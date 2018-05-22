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
	_graphism = std::make_unique<Graphism>(&m_core);
	_state = NOTCONNECTED;
	_playerId = -1;
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
}

void Indie::Core::checkAppContext(AppState context)
{
	static AppState old = AppState::NONE;

	if (context == old)
		return;
	old = context;
	if (context == LAUNCH_SERVER && _state == NOTCONNECTED) {
		std::thread(&Indie::Server::runServer).detach();
		_state = WAITING;
		// >> mettre un try / catch en boucle ?
		usleep(5000);
		_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
		_playerId = waitForId();
		// <<
	}
	if (context == READY && _state == WAITING)
		dprintf(_socket->getFd(), "READY\n");
	if (context == CONNECT && _state == NOTCONNECTED) {
		// si socket fail (try / catch) : _state = NOTCONNECTED + on change pas de menu
		_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
		_state = WAITING;
		_playerId = waitForId();
	}
}

std::string floatToInt(float nb)
{
	std::stringstream ss;
	ss << std::setprecision(6) << nb;
	return ss.str();
}

void Indie::Core::run()
{
	irr::core::vector3df prevPos, pos;
	AppContext context;

	context.options = &m_opts;
	context.menu = &m_menu;
	context.device = m_core.m_device;
	context.state = &m_state;
	m_event.load(context);
	_mapper = std::make_unique<Map>("assets/maps/map.txt", 20.0f, 100.0f, _graphism);
	m_splash.display(m_core.m_device, m_event);
	m_menu.loadMenu(m_core.m_device, m_opts);
	while (m_core.m_device->run() && m_run) {
		processEvents();
		m_core.m_driver->beginScene(true, true, _color);
		checkAppContext(*(context.state));
		if (_state != NOTCONNECTED)
			readServerInformations(_socket->readSocket()); // Must be before drawall, readServer apply position, drawAll do collision
		if (m_state == PLAY) {
			 m_core.getCamera().change(m_core.getSceneManager());
			m_core.m_device->getCursorControl()->setVisible(false);
			prevPos = _playerObjects[0]->getPosition();
			pos = _playerObjects[0]->move(m_event);

			if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
				_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + floatToInt(pos.X) + ':' + floatToInt(pos.Y) + ':' + floatToInt(pos.Z) + ':'  + std::to_string(_playerObjects[0]->getRotation().Y));
			readServerInformations(_socket->readSocket()); // Must be before drawall, readServer apply position, drawAll do collision
			m_core.m_sceneManager->drawAll(); // draw and do collision
		 } else {
			m_core.m_device->getCursorControl()->setVisible(true);
		 	m_core.m_gui->drawAll();//handleMenu();
			m_core.getCamera().change(m_core.getSceneManager());
		}
		m_core.m_driver->endScene();
		drawCaption();
	}
}