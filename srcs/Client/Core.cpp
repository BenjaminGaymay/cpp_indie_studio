/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <iostream>
#include <Player.hpp>
#include <Bomb.hpp>
#include <algorithm>
#include "Core.hpp"
#include "Map.hpp"
#include "ManageStrings.hpp"

Indie::Core::Core() : _lastFps(-1), m_opts(1280, 720, false)
{
	_playersFct.push_back(&Indie::Core::addPlayer);
	_playersFct.push_back(&Indie::Core::removePlayer);
	_playersFct.push_back(&Indie::Core::movePlayer);
	m_state = MENU;
	m_run = true;
	_color = {255, 168, 201, 255};
	m_core.initWindow(m_event, m_opts);
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
	MenuState res = NONE;

	m_core.m_device->getCursorControl()->setVisible(true);
	res = m_menu.display();
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
	AppContext context;
	Graphism graphism(&m_core);
	_mapper = std::make_unique<Map>("assets/maps/map.txt", 20.0f, 100.0f, graphism);

	context.device = m_core.m_device;
	context.menu = &m_menu;
	context.options = &m_opts;
	m_event.load(context);

	m_splash.display(m_core.m_device, m_event);
	m_menu.loadMenu(m_core.m_device, m_opts);
	_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
	_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(waitForId(graphism), graphism.createTexture(*graphism.getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true)));
	graphism.resizeNode(_playerObjects[0]->getPlayer(), _mapper->getSize());
	_playerObjects[0]->setSpeed(1);
	// m_state = GAME;
	// m_core.getCamera().change(m_core.getSceneManager());
	while (m_core.m_device->run() && m_run) {
		processEvents();
    		m_core.m_driver->beginScene(true, true, _color);
    		readServerInformations(_socket->readSocket(), graphism);

    		auto prevPos = _playerObjects[0]->getPosition();
    		auto pos = _playerObjects[0]->move(m_event);

    		// >> un fct pour envoyer tous les events ?
    		if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
      			_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z));
		    // << un fct pour envoyer tous les events ?

    		m_core.m_sceneManager->drawAll();
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