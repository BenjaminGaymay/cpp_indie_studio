/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <Player.hpp>
#include <Bomb.hpp>
#include <algorithm>
#include <iomanip>
#include "Core.hpp"
#include "Map.hpp"
#include "ManageStrings.hpp"
#include "Server.hpp"

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
	_graphism = std::make_unique<Graphism>(&m_core);
	_state = NOTCONNECTED;
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
	}
}

void Indie::Core::processEvents()
{
	if (m_event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (m_event.isKeyDown(irr::KEY_KEY_A))
		std::cout << m_event.MouseState.Position.X << " : "
				  << m_event.MouseState.Position.Y << std::endl;
	// BOUTON POUR LANCER SERVEUR / HOST SE CO AUTOMATIQUEMENT
	if (m_event.isKeyDown(irr::KEY_KEY_L) && _state == NOTCONNECTED) {
		std::thread(&Indie::Server::runServer).detach();
		_state = WAITING;
		// >> mettre un try / catch en boucle ?
		usleep(5000);
		_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
		// <<
		_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(waitForId(), _graphism->createTexture(*_graphism->getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true)));
		_graphism->resizeNode(_playerObjects[0]->getPlayer(), _mapper->getSize());
	}
	// BOUTON PRET A LANCER LA PARTIE
	if (m_event.isKeyDown(irr::KEY_KEY_R) && _state == WAITING)
		dprintf(_socket->getFd(), "READY\n");
	// BOUTON CONNEXION AU SERVER
	if (m_event.isKeyDown(irr::KEY_KEY_C)) {
		_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
		_state = WAITING;
		_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(waitForId(), _graphism->createTexture(*_graphism->getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true)));
		_graphism->resizeNode(_playerObjects[0]->getPlayer(), _mapper->getSize());
	}
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
			if (_state != PLAYING)
				break;
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
	irr::core::vector3df prevPos, pos;

	_mapper = std::make_unique<Map>("assets/maps/map.txt", 20.0f, 100.0f, _graphism);
	m_menu.loadMenu(m_core.m_device);
	m_splash.display(m_core.m_device, m_event);
	while (m_core.m_device->run() && m_run) {
		processEvents();
		m_core.m_driver->beginScene(true, true, _color);
		if (_state != NOTCONNECTED)
			readServerInformations(_socket->readSocket()); // Must be before drawall, readServer apply position, drawAll do collision
		if (m_state == MENU) {
			handleMenu();
		} else if (m_state == MAPPING) {
			std::cout << "mdr" << std::endl;
			exit(0);
		} else {
			m_core.m_device->getCursorControl()->setVisible(false);
			prevPos = _playerObjects[0]->getPosition();
			pos = _playerObjects[0]->move(m_event);

			if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
				_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z) + ':'  + std::to_string(_playerObjects[0]->getRotation().Y));
			m_core.m_sceneManager->drawAll(); // draw and do collision
		}
		m_core.m_driver->endScene();
		drawCaption();
	}
}