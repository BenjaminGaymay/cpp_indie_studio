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
#include <irrKlang.h>
#include "Core.hpp"
#include "EventManager.hpp"

Indie::Core::Core()
	:_lastFps(-1), _engine(irrklang::createIrrKlangDevice()), _game(std::make_unique<Game>())
{
	if (!_engine)
		throw std::logic_error("bha la music déconne.");
}

Indie::Core::~Core()
{
	_engine->drop();
}

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
	if (_chat._getch)
		return _chat.manageTchat(m_event, _socket);
	if (m_event.isKeyDown(irr::KEY_ESCAPE)) {
		m_event.setKeyUp(irr::KEY_ESCAPE);
		if (m_state == PLAY or m_state == SPEC) {
			m_core.m_device->getCursorControl()->setVisible(true);
			m_core.getCamera().change(m_core.getSceneManager(), Camera::BASIC);
			m_menu.m_gameOptions->setVisible(true);
		}
	}
	if (m_event.isKeyDown(irr::KEY_RETURN)) {
			m_event.setKeyUp(irr::KEY_RETURN);
			if (_socket) {
				_chat._getch = true;
				_chat._textBox->setVisible(true);
				m_core.m_gui->setFocus(_chat._textBox);
				_chat._textBox->setText(L"");
			}
	}
	m_evtManager->manage(_engine);
}

void Indie::Core::checkAppContext()
{
	static AppState old = AppState::NONE;
	static std::string oldMap;

	if (m_state == old)
		return;
	old = m_state;
	if (m_state == LAUNCH_SERVER && _state == NOTCONNECTED) {
		std::thread(&Indie::Server::runServer).detach();
		while (true) {
			try {
				_socket = std::make_unique<Socket>(5567, "127.0.0.1", Socket::CLIENT);
				break;
			} catch (const std::exception &e) {}
		}
		_state = WAITING;
		oldMap = "";
		_playerId = waitForId();
	}
	if (m_state == READY && _state == WAITING) {
		if (_playerId == 0) {
			irr::gui::IGUIListBox *list = static_cast<irr::gui::IGUIListBox*>(m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_LIST_MAP, true));
			auto map = ManageStrings::convertWchart(list->getListItem(list->getSelected()));

			if (map != oldMap) {
				sendMapToServer(std::string("assets/maps/" + map));
				oldMap = map;
			}
		}
		dprintf(_socket->getFd(), "%d:%d\n", GAMEINFOS, EV_READY);
	}
	if (m_state == UNREADY && _state == WAITING)
		dprintf(_socket->getFd(), "%d:%d\n", GAMEINFOS, EV_UNREADY);
	if (m_state == CONNECT && _state == NOTCONNECTED) {
		try {
			_socket = std::make_unique<Socket>(5567, ManageStrings::convertWchart(m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_IP, true)->getText()), Socket::CLIENT);
			_state = WAITING;
			_playerId = waitForId();
		} catch (const std::exception &e) {
			m_state = MENU;
			m_menu.m_roomC->setVisible(false);
			m_menu.m_join->setVisible(true);
		}
	}
	if (m_state == SERVER_DOWN) {
		_state = NOTCONNECTED;
		if (m_menu.m_roomS->isVisible())
			m_menu.m_roomS->setVisible(false);
		else if (m_menu.m_roomC->isVisible())
			m_menu.m_roomC->setVisible(false);
		m_menu.m_down->setVisible(true);
	}
}

void Indie::Core::exitGame()
{
	auto &mapper = _game->getMapperEdit();

	// Y A DES TRUCS QUI SE DELETE PAS (lancer deux joueurs / quitter le serveur / lancer un serveur sur le second et jouer)
	if (_state != NOTCONNECTED)
		dprintf(_socket->getFd(), "%d:%d:%d\n", PLAYER, LEAVE, _playerObjects[0]->getId());
	_readyPlayers.clear();
	_game->clear3dMap();
	mapper.release();
	_playerObjects.clear();
	_socket->closeSocket();
	_socket.release();
	_chat._messages.clear();
	if (_chat._textBox->isVisible())
		_chat._textBox->setVisible(false);
	_playerId = -1;
	_socket = nullptr;
	_state = NOTCONNECTED;
	m_core.getCamera().change(m_core.getSceneManager(), Camera::BASIC);
	m_core.m_device->getCursorControl()->setVisible(true);
}

void Indie::Core::run()
{
	irrklang::ISound* music = _engine->play2D("music/main.wav", true, false, true);
	music->setVolume(m_opts.getMusic() ? 0.3 : 0);
	if (m_opts.getSplashScreen())
		m_splash.display(m_core.m_device, m_event);
	m_menu.loadMenu(m_core.m_device, m_opts);
	_chat._textBox = m_core.m_gui->addEditBox(L"", irr::core::rect<irr::s32>(50, m_opts.getHeight() - 40, 1020, m_opts.getHeight() - 10), true, m_menu.m_root, GUI_ID_TCHAT_BUTTON);
	_chat._textBox->setMax(40);
	_chat._textBox->setVisible(false);

	m_core.getCamera().change(m_core.getSceneManager(), Camera::BASIC);
	m_core.m_device->getCursorControl()->setVisible(true);
	while (m_core.m_device->run() && m_run) {
		processEvents();
		m_core.m_driver->beginScene(true, true, _color);
		checkAppContext();
		checkAppState();
		m_core.m_gui->drawAll();
		_chat.printTchat(m_core, m_opts);
		m_core.m_driver->endScene();
		drawCaption();
	}
	music->drop();
}

void Indie::Core::infoReadyPlayerOne()
{
	std::string msg;
	int y = 0;
	for (auto &aReadyPlayer : _readyPlayers) {
		msg = (aReadyPlayer.second == EV_READY ? ":READY" : ":UNREADY");
		m_core.m_font->draw(
				irr::core::stringw((std::to_string(aReadyPlayer.first) + msg).c_str()),
				irr::core::rect<irr::s32>(m_opts.getWidth() - 250, y, 0, 0),
				irr::video::SColor(255, 255, 255, 255));
		y += 30;
	}
}

void Indie::Core::checkAppState()
{
	if (_state != NOTCONNECTED && _socket) {
		try {
			readServerInformations(_socket->readSocket());
		} catch (const std::exception &e) {
			exitGame();
			m_state = SERVER_DOWN;
		}
	}
	switch (m_state) {
		case PLAY:
			if (m_event.isKeyDown(irr::KEY_KEY_H)) {
				_socket->sendInfos(Indie::GAMEINFOS, Indie::INFO, "");
				m_event.setKeyUp(irr::KEY_KEY_H);
			}
			pos = _playerObjects[0]->getPosition();
			m_core.getCamera().m_cameras[Indie::Camera::FPS]->setPosition({pos.X, pos.Y + 200, pos.Z});
			m_core.getCamera().m_cameras[Indie::Camera::FPS]->setRotation({90, 90, 0});
			moveEvent(pos);
			dropBombEvent(pos);
			m_core.m_sceneManager->drawAll();
			break;
		case SPEC:
			m_core.m_sceneManager->drawAll();
			break;
		case MAPPING:
			_graphism->clearNode();
			if (_game) {
				_game->clear3dMap();
				_game->clear2dMap();
			}
			editMap();
			m_state = MENU;
		case LOCAL:
			m_core.m_sceneManager->drawAll();
			break;
		default:
			break;
	}
	switch (_state) {
		case NOTCONNECTED : _readyPlayers.clear(); break;
		case WAITING : infoReadyPlayerOne(); break;
		default: _readyPlayers.clear(); break;
	}
}

void Indie::Core::init(Options &opt)
{
	m_opts = opt;
	m_evtManager = std::make_unique<EventManager>(this);
	_objectsFct.push_back(&Indie::Core::comPlayer);
	_objectsFct.push_back(&Indie::Core::comGameInfos);
	_objectsFct.push_back(&Indie::Core::comMap);
	_objectsFct.push_back(&Indie::Core::comBomb);
	m_state = MENU;
	m_run = true;
	_color = {255, 168, 201, 255};
	m_core.initWindow(m_event, m_opts);
	m_core.m_sceneManager->setAmbientLight({255.0, 255.0, 255.0});
	_graphism = std::make_unique<Graphism>(&m_core);
	_state = NOTCONNECTED;
	_playerId = -1;
	_socket = nullptr;
	_chat._getch = false;
}