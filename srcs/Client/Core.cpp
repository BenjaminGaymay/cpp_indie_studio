//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#include <sstream>
#include <thread>
#include <Player.hpp>
#include <iomanip>
#include "Core.hpp"

Indie::Core::Core() : _lastFps(-1), m_opts(1280, 720, false)
{
	_objectsFct.push_back(&Indie::Core::comPlayer);
	_objectsFct.push_back(&Indie::Core::comGameInfos);
	_objectsFct.push_back(&Indie::Core::comMap);
	m_state = MENU;
	m_run = true;
	_color = {255, 168, 201, 255};
	m_core.initWindow(m_event, m_opts);
	m_core.m_sceneManager->setAmbientLight({255.0, 255.0, 255.0});
	_graphism = std::make_unique<Graphism>(&m_core);
	_state = NOTCONNECTED;
	_playerId = -1;
	_socket = nullptr;
	m_bappe = true;
	_tchat._getch = false;
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
	if (_tchat._getch)
		manageTchat();
	else {
		if (m_event.isKeyDown(irr::KEY_ESCAPE))
			m_run = false;
		if (m_event.isKeyDown(irr::KEY_KEY_A)) {
			std::cout << m_event.MouseState.Position.X << " : "
					<< m_event.MouseState.Position.Y << std::endl;
			m_event.setKeyUp(irr::KEY_KEY_A);
		}
		if (m_event.isKeyDown(irr::KEY_KEY_T)) {
			m_event.setKeyUp(irr::KEY_KEY_T);
			if (_socket) {
				_tchat._getch = true;
				_tchat._textBox->setVisible(true);
				m_core.m_gui->setFocus(_tchat._textBox);
				_tchat._textBox->setText(L"");
			}
		}
	}
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
	irr::core::vector3df pos;

	m_splash.display(m_core.m_device, m_event);
	m_menu.loadMenu(m_core.m_device, m_opts);
	_tchat._textBox = m_core.m_gui->addEditBox(L"", irr::core::rect<irr::s32>(50, m_opts.getHeight() - 40, 1020, m_opts.getHeight() - 10), true, m_menu.m_root, GUI_ID_TCHAT_BUTTON);
	_tchat._textBox->setMax(40);
	_tchat._textBox->setVisible(false);

	while (m_core.m_device->run() && m_run) {
		processEvents();
		m_core.m_driver->beginScene(true, true, _color);
		checkAppContext();

		if (_state != NOTCONNECTED && _socket)
			readServerInformations(_socket->readSocket()); // Must be before drawall, readServer apply position, drawAll do collision
		if (m_state == PLAY) {
			m_core.getCamera().change(m_core.getSceneManager());
			m_core.m_device->getCursorControl()->setVisible(false);
			pos = _playerObjects[0]->getPosition();
			moveEvent(pos);
			dropBombEvent(pos);
			m_core.m_sceneManager->drawAll();
		} else if (m_state == MAPPING) {
			editMap();
			m_state = MENU;
		} else {
			m_core.m_device->getCursorControl()->setVisible(true);
			m_core.getCamera().change(m_core.getSceneManager());
		}
		m_core.m_gui->drawAll();//handleMenu();
		printTchat();
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
					m_menu.m_mapMenu->setVisible(true);
					break;
				case GUI_ID_MAP_BACK_BUTTON:
					m_menu.m_main->setVisible(true);
					m_menu.m_mapMenu->setVisible(false);
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
					m_menu.m_mapMenu->setVisible(false);
					m_menu.m_mapEdit->setVisible(true);
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
				case GUI_ID_MAP_SAVE_BUTTON:
					m_menu.m_mapEdit->setVisible(false);
					m_menu.m_mapMenu->setVisible(true);
					m_bappe = false;
					break;
				default:
					break;
			}
		}
	}
}