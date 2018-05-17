/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <sstream>
#include <iostream>
#include <Player.hpp>
#include <Bomb.hpp>
#include <algorithm>
#include <iomanip>
#include "Core.hpp"
#include "Map.hpp"
#include "ManageStrings.hpp"

Indie::Core::Core() : _lastFps(-1)
{
	_playersFct.push_back(&Indie::Core::addPlayer);
	_playersFct.push_back(&Indie::Core::removePlayer);
	_playersFct.push_back(&Indie::Core::movePlayer);
	m_state = MENU;
	m_run = true;
	_color = {255, 168, 201, 255};
	m_core.initWindow(m_event);
	m_core.m_sceneManager->setAmbientLight({255.0, 255.0, 255.0});
}

Indie::Core::~Core()
{}

void Indie::Core::drawCaption()
{
	int fps = m_core.m_driver->getFPS();

	if (_lastFps != fps) {
		irr::core::stringw str = L"Irrlicht Engine - Bomberman [";
		str += m_core.m_driver->getName();
		str += "] FPS:";
		str += fps;
		m_core.m_device->setWindowCaption(str.c_str());
		_lastFps = fps;
		std::cout << "FPS: " << _lastFps << std::endl;
	}
}

void Indie::Core::processEvents()
{
	if (m_event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (m_event.isKeyDown(irr::KEY_KEY_A))
		std::cout << m_event.MouseState.Position.X << " : "
				  << m_event.MouseState.Position.Y << std::endl;
}

void Indie::Core::handleMenu()
{
	MenuState res;

	m_core.m_device->getCursorControl()->setVisible(true);
	res = m_menu.display(m_event);
	switch (res) {
		case QUIT:
			m_run = false;
			break;
		case PLAY:
			m_state = GAME;
			m_core.getCamera().change(m_core.getSceneManager());
			break;
		case GEN_MAP:
			m_state = MAPPING;
			break;
		default:
			break;
	}
}

void Indie::Core::run()
{
	Graphism graphism(&m_core);
	_mapper = std::make_unique<Map>("assets/maps/map.txt", 20.0f, 100.0f, graphism);
	m_menu.loadMenu(m_core.m_device);

	m_splash.display(m_core.m_device, m_event);
	_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
	_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(waitForId(graphism), graphism.createTexture(*graphism.getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true)));
	graphism.resizeNode(_playerObjects[0]->getPlayer(), _mapper->getSize());
	_playerObjects[0]->setSpeed(1);
	irr::core::vector3df prevPos, pos;
	while (m_core.m_device->run() && m_run) {
			processEvents();
    		m_core.m_driver->beginScene(true, true, _color);
    		prevPos = _playerObjects[0]->getPosition();
    		pos = _playerObjects[0]->move(m_event);

			if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
				_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z) + ':'  + std::to_string(_playerObjects[0]->getPlayer()->getRotation().Y));
			readServerInformations(_socket->readSocket(), graphism); // Must be before drawall, readServer apply position, drawAll do collision
    		m_core.m_sceneManager->drawAll(); // draw and do collision
    		if (m_state == MENU) {
			handleMenu();
		} else if (m_state == MAPPING) {
			std::cout << "mdr" << std::endl;
		    	exit(0);
		} else {
			m_core.m_device->getCursorControl()->setVisible(false);
		}
		m_core.m_driver->endScene();
		drawCaption();
	}
}