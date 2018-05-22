/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <sstream>
#include <iostream>
#include <random>
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
		while (1) {
			try {
				_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
				break;
			} catch (const std::exception &e) {}
		}
		_playerId = waitForId();
		// <<
	}
	if (context == READY && _state == WAITING)
		dprintf(_socket->getFd(), "READY\n");
	if (context == CONNECT && _state == NOTCONNECTED) {
		// si socket fail (try / catch) : _state = NOTCONNECTED + on change pas de menu
		try {
			_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
			_state = WAITING;
			_playerId = waitForId();
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

void Indie::Core::create_rand_map(std::string name, size_t x, size_t y)
{
	std::string file = "assets/maps/" + name;
	std::vector<std::vector<int>> map;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,1);

	if (x < 10 || y < 10 || x > 50 || y > 50) {
		std::cerr << "x and y minimum values are 10" << std::endl;
		exit(0);
	}
	for (std::size_t i = 0; i < y; ++i) {
		std::vector<int> line;
		for (std::size_t j = 0; j < x; ++j) {
			line.push_back(distribution(generator));
		}
		map.push_back(line);
	}

	for (std::size_t i = 0; i < x; ++i) {
		map[0][i] = 1;
		map[y - 1][i] = 1;
	}

	for (std::size_t i = 0; i < y; ++i) {
		map[i][0] = 1;
		map[i][x - 1] = 1;
	}

	// TOP LEFT CORNER
	map[1][1] = 0;
	map[1][2] = 0;
	map[2][1] = 0;

	// TOP RIGHT CORNER
	map[1][x - 2] = 0;
	map[1][x - 3] = 0;
	map[2][x - 2] = 0;

	// BOT LEFT CORNER
	map[y - 2][1] = 0;
	map[y - 2][2] = 0;
	map[y - 3][1] = 0;

	// BOT RIGHT CORNER
	map[y - 2][x - 2] = 0;
	map[y - 2][x - 3] = 0;
	map[y - 3][x - 2] = 0;

	write_in_file(file, map);
}

void Indie::Core::createZeroMap(std::string name, size_t x, size_t y)
{
	std::string file = "assets/maps/" + name;
	std::vector<std::vector<int>> map;

	for (int i = 0; i < y; ++i) {
		std::vector<int> line;
		for (int j = 0; j < x; ++j) {
			line.push_back(0);
		}
		map.push_back(line);
	}
	write_in_file(file, map);
}


void Indie::Core::write_in_file(std::string file, std::vector<std::vector<int>> map)
{
	std::ofstream outfile (file);

	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			outfile << "0" << map[i][j] << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}

void Indie::Core::cleanMap()
{
	size_t min = _mapper->getMap2d()[0].size();
	size_t max = 0;

	for (size_t i = 0; i < 50; ++i) {
		for (size_t j = 0; j < 50; ++j) {
			std::cout << _mapper->getMap2d()[i][j];
		}
		std::cout << std::endl;
	}
	while (std::find(std::begin(_mapper->getMap2d()[0]), std::end(_mapper->getMap2d()[0]), 1) != std::end(_mapper->getMap2d()[0]) == 0)
		_mapper->getMap2d().erase(_mapper->getMap2d().begin());
	int i = _mapper->getMap2d().size() - 1;
	while (std::find(std::begin(_mapper->getMap2d()[i]), std::end(_mapper->getMap2d()[i]), 1) != std::end(_mapper->getMap2d()[i]) == 0) {
		_mapper->getMap2d().erase(_mapper->getMap2d().end());
		--i;
	}
	for (size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		for (size_t j = 0; j < _mapper->getMap2d()[i].size(); ++j) {
			if (_mapper->getMap2d()[i][j] == 1 && min > j) {
				min = j;
				break;
			}
		}
		for (size_t j = _mapper->getMap2d()[i].size() - 1; j > 0; --j) {
			if (_mapper->getMap2d()[i][j] == 1 && max < j) {
				max = j + 1;
				break;
			}
		}
	}
	for (size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		_mapper->getMap2d()[i].erase(_mapper->getMap2d()[i].begin() + max, _mapper->getMap2d()[i].end());
		_mapper->getMap2d()[i].erase(_mapper->getMap2d()[i].begin(), _mapper->getMap2d()[i].begin() + min);
	}
}

int Indie::Core::EditMapEvents()
{
	if (m_event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (m_event.isKeyDown(irr::KEY_KEY_S)) {
		cleanMap();
		return -1;
	}
	if (m_event.MouseState.LeftButtonDown == true) {
		m_event.MouseState.LeftButtonDown = false;
		int x = int((m_event.MouseState.Position.X - 268) / 18.6);
		int y = int((m_event.MouseState.Position.Y - 16) / 18.6);
		if (x >= 0 && y >= 0 && x < 50 && y < 50)
			_mapper->getMap2d()[y][x] = (_mapper->getMap2d()[y][x] == 1 ? _mapper->getMap2d()[y][x] = 0 : _mapper->getMap2d()[y][x] = 1);
		// for (size_t i = 0; i < 50; ++i) {
		// 	for (size_t j = 0; j < 50; ++j) {
		// 		std::cout << _mapper->getMap2d()[i][j];
		// 	}
		// 	std::cout << std::endl;
		//}
	}
}

void Indie::Core::editMap()
{
	m_core.editMapView(m_event);
	createZeroMap("mdr.txt", 50, 50);
	_mapper = std::make_unique<Map>("assets/maps/mdr.txt", 20.0f, 100.0f, _graphism);
	std::vector<std::vector<int>> mdr = _mapper->getMap2d();
	while (m_core.m_device->run() && m_run) {
		if (EditMapEvents() == -1)
			break;
		m_core.m_driver->beginScene(true, true, _color);
    		m_core.m_sceneManager->drawAll();
		m_core.m_driver->endScene();
	}
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
		if (_state != NOTCONNECTED && _socket)
			readServerInformations(_socket->readSocket()); // Must be before drawall, readServer apply position, drawAll do collision
		if (m_state == PLAY) {
			 m_core.getCamera().change(m_core.getSceneManager());
			m_core.m_device->getCursorControl()->setVisible(false);
			prevPos = _playerObjects[0]->getPosition();
			pos = _playerObjects[0]->move(m_event);

			if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
				_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z) + ':'  + std::to_string(_playerObjects[0]->getRotation().Y));
			m_core.m_sceneManager->drawAll(); // draw and do collision
		} else if (m_state == MAPPING) {
			editMap();
			// create_rand_map("mdr.txt", 50, 50);
			// _mapper = std::make_unique<Map>("assets/maps/mdr.txt", 20.0f, 100.0f, graphism);
			m_state = MENU;
		} else {
			m_core.m_device->getCursorControl()->setVisible(true);
		 	m_core.m_gui->drawAll();//handleMenu();
			m_core.getCamera().change(m_core.getSceneManager());
		m_core.m_driver->endScene();
		drawCaption();
		}
	}
}