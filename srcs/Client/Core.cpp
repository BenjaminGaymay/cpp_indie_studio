//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#include <thread>
#include <Player.hpp>
#include "Core.hpp"

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
	_socket = nullptr;
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
	menuEvents();
}

void Indie::Core::checkAppContext()
{
	static AppState old = AppState::NONE;

	if (m_state == old)
		return;
	old = m_state;
	if (m_state == LAUNCH_SERVER && _state == NOTCONNECTED) {
		std::thread(&Indie::Server::runServer).detach();
		_state = WAITING;
		while (1) {
			try {
				_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
				break;
			} catch (const std::exception &e) {}
		}
		_playerId = waitForId();
		// >> on gerera ca dans la room de l'host
		sendMapToServer("assets/maps/map.txt");
		// <<
	}
	if (m_state == READY && _state == WAITING)
		dprintf(_socket->getFd(), "READY\n");
	if (m_state == CONNECT && _state == NOTCONNECTED) {
		try {
			_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
			_state = WAITING;
			_playerId = waitForId();
		} catch (const std::exception &e) {
			m_state = MENU;
			m_menu.m_room->setVisible(false);
			m_menu.m_play->setVisible(true);
		}
	}
}

void Indie::Core::run()
{
	irr::core::vector3df prevPos, pos;

	m_splash.display(m_core.m_device, m_event);
	m_menu.loadMenu(m_core.m_device, m_opts);
	while (m_core.m_device->run() && m_run) {
		processEvents();
		m_core.m_driver->beginScene(true, true, _color);
		checkAppContext();
		if (_state != NOTCONNECTED && _socket)
			readServerInformations(_socket->readSocket()); // Must be before drawall, readServer apply position, drawAll do collision
		if (m_state == PLAY) {
			m_core.getCamera().change(m_core.getSceneManager());
			m_core.m_device->getCursorControl()->setVisible(false);
			prevPos = _playerObjects[0]->getPosition();
			pos = _playerObjects[0]->move(m_event);

			if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z) {
				irr::core::vector2di pos2d = _mapper->get2dBlock(pos);
				_socket->sendInfos(Indie::PLAYER, Indie::MOVE,
								   std::to_string(_playerObjects[0]->getId()) + ':' +
								   std::to_string(pos2d.X) + ':' + // ajout seg dans connectionWithServer je c pas pk
								   std::to_string(pos2d.Y) + ':' + // ajout ci dessus
								   std::to_string(pos.X) + ':' +
								   std::to_string(pos.Y) + ':' +
								   std::to_string(pos.Z) + ':' +
								   std::to_string(_playerObjects[0]->getRotation().Y));
			}
			m_core.m_sceneManager->drawAll(); // draw and do collision
		} else if (m_state == MAPPING) {
			editMap();
			m_state = MENU;
		} else {
			m_core.m_device->getCursorControl()->setVisible(true);
		 	m_core.m_gui->drawAll();//handleMenu();
			m_core.getCamera().change(m_core.getSceneManager());
		}
		m_core.m_driver->endScene();
		drawCaption();
	}
}

void Indie::Core::menuEvents()
{
	for (std::size_t id = 0; id < BTN_COUNT; id++) {
		if (m_event.isButtonClicked(static_cast<IdGui>(id))) {
			switch (id) {
				case GUI_ID_QUIT_BUTTON:
					m_core.m_device->closeDevice();
					break;
				case GUI_ID_PLAY_BUTTON:
					m_menu.m_main->setVisible(false);
					m_menu.m_play->setVisible(true);
					break;
				case GUI_ID_OPTIONS_BUTTON:
					m_menu.m_main->setVisible(false);
					m_menu.m_option->setVisible(true);
					break;
				case GUI_ID_MAP_BUTTON:
					m_menu.m_main->setVisible(false);
					m_menu.m_mapEdit->setVisible(true);
					break;
				case GUI_ID_MAP_BACK_BUTTON:
					m_menu.m_main->setVisible(true);
					m_menu.m_mapEdit->setVisible(false);
					break;
				case GUI_ID_PLAY_BACK_BUTTON:
					m_menu.m_main->setVisible(true);
					m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_ROOM_BACK_BUTTON:
					m_menu.m_play->setVisible(true);
					m_menu.m_room->setVisible(false);
					break;
				case GUI_ID_OPTION_BACK_BUTTON:
					m_menu.m_main->setVisible(true);
					m_menu.m_option->setVisible(false);
					break;
				case GUI_ID_MAP_RANDOM_BUTTON:
					createRandMap("azerty.txt", 50, 50);
					//m_menu.m_mapEdit->setVisible(false);
					break;
				case GUI_ID_MAP_EDITOR_BUTTON:
					m_state = MAPPING;
					m_menu.m_mapEdit->setVisible(false);
					break;
				case GUI_ID_READY:
					m_state = READY;
					m_menu.m_room->setVisible(false);
					break;
				case GUI_ID_PLAY_CLIENT:
					m_state = CONNECT;
					m_menu.m_room->setVisible(true);
					m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_PLAY_SERVER:
					m_state = LAUNCH_SERVER;
					m_menu.m_room->setVisible(true);
					m_menu.m_play->setVisible(false);
					break;
				default:
					break;
			}
		}
	}
}