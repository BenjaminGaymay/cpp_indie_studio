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
		if (m_event.isKeyDown(irr::KEY_ESCAPE)) {
			m_event.setKeyUp(irr::KEY_ESCAPE);
			if (m_state == PLAY) {
				m_core.m_device->getCursorControl()->setVisible(true);
				m_core.getCamera().change(m_core.getSceneManager(), Camera::BASIC);
				m_menu.m_gameOptions->setVisible(true);
			}
		}
		if (m_event.isKeyDown(irr::KEY_RETURN)) {
			m_event.setKeyUp(irr::KEY_RETURN);
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
				_socket = std::make_unique<Socket>(5567, "127.0.0.1", Socket::CLIENT);
				break;
			} catch (const std::exception &e) {}
		}
		_playerId = waitForId();
	}
	if (m_state == READY && _state == WAITING) {
		if (_playerId == 0) {
			irr::gui::IGUIListBox *list = static_cast<irr::gui::IGUIListBox*>(m_core.m_gui->getRootGUIElement()->getElementFromId(ID_GUI_LIST_MAP, true));
			auto map = ManageStrings::convertWchart(list->getListItem(list->getSelected()));
			sendMapToServer(std::string("assets/maps/" + map));
		}
		dprintf(_socket->getFd(), "READY\n");
	}
	if (m_state == CONNECT && _state == NOTCONNECTED) {
		try {
			_socket = std::make_unique<Socket>(5567, "127.0.0.1", Socket::CLIENT);
			_state = WAITING;
			_playerId = waitForId();
		} catch (const std::exception &e) {
			m_state = MENU;
			m_menu.m_roomC->setVisible(false);
			m_menu.m_play->setVisible(true);
		}
	}
	if (m_state == SERVER_DOWN) {
		if (m_menu.m_roomS->isVisible())
			m_menu.m_roomS->setVisible(false);
		else if (m_menu.m_roomC->isVisible())
			m_menu.m_roomC->setVisible(false);
		m_menu.m_down->setVisible(true);
	}
}

/*std::string floatToInt(float nb)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(6) << nb;
	return ss.str();
}*/

void Indie::Core::exitGame()
{
	// Y A DES TRUCS QUI SE DELETE PAS (lancer deux joueurs / quitter le serveur / lancer un serveur sur le second et jouer)
	_mapper.release();
	_playerObjects.clear();
	_socket->closeSocket();
	_socket.release();
	_tchat._messages.clear();
	if (_tchat._textBox->isVisible())
		_tchat._textBox->setVisible(false);
	_playerId = -1;
	_state = NOTCONNECTED;
	m_core.getCamera().change(m_core.getSceneManager(), Camera::BASIC);
	m_core.m_device->getCursorControl()->setVisible(true);
}

void Indie::Core::run()
{
	irr::core::vector3df prevPos, pos;

	m_splash.display(m_core.m_device, m_event);
	m_menu.loadMenu(m_core.m_device, m_opts);
	_tchat._textBox = m_core.m_gui->addEditBox(L"", irr::core::rect<irr::s32>(50, m_opts.getHeight() - 40, 1020, m_opts.getHeight() - 10), true, m_menu.m_root, GUI_ID_TCHAT_BUTTON);
	_tchat._textBox->setMax(40);
	_tchat._textBox->setVisible(false);

	m_core.getCamera().change(m_core.getSceneManager(), Camera::BASIC);
	m_core.m_device->getCursorControl()->setVisible(true);
	while (m_core.m_device->run() && m_run) {
		processEvents();
		m_core.m_driver->beginScene(true, true, _color);
		checkAppContext();

		if (_state != NOTCONNECTED && _socket) {
			try {
				readServerInformations(_socket->readSocket());
			} catch (const std::exception &e) {
				exitGame();
				m_state = SERVER_DOWN;
			}
		}
		if (m_state == PLAY) {
			prevPos = _playerObjects[0]->getPosition();
			pos = _playerObjects[0]->move(m_event);

			if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z) {
				irr::core::vector2di pos2d = _mapper->get2dBlock(pos + _mapper->getSize() / 2);
				_socket->sendInfos(Indie::PLAYER, Indie::MOVE,
							std::to_string(_playerObjects[0]->getId()) + ':' +
							std::to_string(pos2d.X) + ':' +
							std::to_string(pos2d.Y) + ':' +
							std::to_string(pos.X) + ':' +
							std::to_string(pos.Y) + ':' +
							std::to_string(pos.Z) + ':' +
							std::to_string(_playerObjects[0]->getRotation().Y));
			}
			m_core.m_sceneManager->drawAll();
		} else if (m_state == MAPPING) {
			editMap();
			m_state = MENU;
		}
		m_core.m_gui->drawAll();
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
					if (_playerId == 0)
						m_menu.m_roomS->setVisible(false);
					else
						m_menu.m_roomC->setVisible(false);
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
					if (_playerId == 0)
						m_menu.m_roomS->setVisible(false);
					else
						m_menu.m_roomC->setVisible(false);
					break;
				case GUI_ID_PLAY_CLIENT:
					m_state = CONNECT;
					m_menu.m_roomC->setVisible(true);
					m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_PLAY_SERVER:
					m_state = LAUNCH_SERVER;
					m_menu.m_roomS->setVisible(true);
					m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_MAP_SAVE_BUTTON:
					m_menu.m_mapEdit->setVisible(false);
					m_menu.m_mapMenu->setVisible(true);
					m_run = false;
					break;
				case GUI_ID_DOWN_BUTTON:
					m_menu.m_down->setVisible(false);
					m_menu.m_main->setVisible(true);
					m_state = MENU;
					break;
				case GUI_ID_LEAVE_GAME_BUTTON:
					exitGame();
					m_state = MENU;
					m_menu.m_gameOptions->setVisible(false);
					m_menu.m_main->setVisible(true);
					break;
				case GUI_ID_QUIT_GAME_BUTTON:
					m_run = false;
					break;
				case GUI_ID_STAY_GAME_BUTTON:
					m_menu.m_gameOptions->setVisible(false);
					m_core.getCamera().change(m_core.getSceneManager(), Camera::FPS);
					m_core.m_device->getCursorControl()->setVisible(false);
					break;
				default:
					break;
			}
		}
	}
}