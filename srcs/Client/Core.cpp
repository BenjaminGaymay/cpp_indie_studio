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

Indie::Core::Core()
{
	_playersFct.push_back(&Indie::Core::addPlayer);
	_playersFct.push_back(&Indie::Core::removePlayer);
	_playersFct.push_back(&Indie::Core::movePlayer);
	m_state = MENU;
}

Indie::Core::~Core()
{}

void Indie::Core::drawCaption(int &lastFps)
{
	int fps = m_core.m_driver->getFPS();

	if (lastFps != fps) {
		irr::core::stringw str = L"Irrlicht Engine - Bomberman [";
		str += m_core.m_driver->getName();
		str += "] FPS:";
		str += fps;
		m_core.m_device->setWindowCaption(str.c_str());
		lastFps = fps;
		std::cout << "FPS: " << lastFps << std::endl;
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
		default:
			break;
	}
}

void Indie::Core::run()
{
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);
	std::vector<std::string> servSend;
	m_core.initWindow(m_event);
	Graphism graphism(m_core);
	m_run = true;
	_mapper = std::make_unique<Map>(20.0f,100.0f);
	_mapper->initMap("/home/benoit/delivery/cpp/cpp_indie_studio/assets/maps/map2.txt");
	_mapper->load(graphism);
	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0, 255.0, 255.0));
	m_menu.loadMenu(m_core.m_device);
	graphism.buildDecor();
	std::vector<Indie::Bomb> bombs;

	m_splash.display(m_core.m_device);
	_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
	_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(waitForId(graphism), graphism.createTexture(*graphism.getTexture(10), {0, 112, 0}, {0, 0, 0}, {0.2f, 0.2f, 0.2f}, true)));


	while (m_core.m_device->run() && m_run) {
		processEvents();
    		m_core.m_driver->beginScene(true, true, color);
    		servSend = _socket->readSocket();
    		readServerInformations(servSend, graphism);

    		auto prevPos = _playerObjects[0]->getPosition();
    		auto pos = _playerObjects[0]->move(m_event);

    		// >> un fct pour envoyer tous les events ?
    		if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
      			_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z));
		    // << un fct pour envoyer tous les events ?

    		m_core.m_sceneManager->drawAll();
    		if (m_state == MENU) {
			handleMenu();
		} else {
			m_core.m_device->getCursorControl()->setVisible(false);
		}
		m_core.m_driver->endScene();
		drawCaption(lastFps);
	}
}