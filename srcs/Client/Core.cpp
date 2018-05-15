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

void Indie::Core::addPlayer(int id, irr::core::vector3df &pos)
{
	std::unique_ptr<ObjectPlayer> newPlayer = std::make_unique<ObjectPlayer>(id, createTexture(_texturesMap[10], pos, {0, 0, 0}, {0.2f, 0.2f, 0.2f}, true));
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(int id, irr::core::vector3df &pos)
{
	std::cout << "remove\n";
	for (auto &p : _playerObjects) {
		if (p->_id == id) {
			_playerObjects.erase(std::find(_playerObjects.begin(), _playerObjects.end(), p));
			return;
		}
	}
}

void Indie::Core::movePlayer(int id, irr::core::vector3df &pos)
{
	for (auto &p : _playerObjects)
		if (p->_id == id)
			p->setPosition(pos);
}

Indie::Core::Core()
{
	generateTextureMap();
	_playersFct.push_back(&Indie::Core::addPlayer);
	_playersFct.push_back(&Indie::Core::removePlayer);
	_playersFct.push_back(&Indie::Core::movePlayer);
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

void Indie::Core::processEvents(const Events &event)
{
	if (event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (event.isKeyDown(irr::KEY_KEY_A))
		std::cout << event.MouseState.Position.X << " : "
				  << event.MouseState.Position.Y << std::endl;
}

int Indie::Core::waitForId()
{
	std::vector<std::string> servSend;

	while (servSend.empty())
		servSend = _socket->readSocket();
	for (auto &c : servSend[0])
		if (!isdigit(c))
			throw std::runtime_error("Communication error");
	return std::stoi(servSend[0]);
}

void Indie::Core::readServerInformations()
{
	auto servSend = _socket->readSocket();
	std::vector<std::string> info;
	int type;
	int event;
	int id;

	for (auto &line : servSend) {
		info = ManageStrings::splitString(line, ':');
		if (!info.empty()) {
			// >> SECURISER CA
			type = std::stoi(info[0]);
			event = std::stoi(info[1]);
			id = std::stoi(info[2]);
			irr::core::vector3df pos(std::stof(info[3]), std::stof(info[4]), std::stof(info[5]));
			// <<

			switch (type) {
				case Indie::PLAYER:
					(this->*_playersFct[event])(id, pos); break;
			}
		}
	}
}


void Indie::Core::run()
{
	Events event;
	Map map;
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);

	m_core.initWindow(event);
	m_run = true;
	map.initMap("assets/maps/map2.txt");
	map.load(*this);
	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0, 255.0, 255.0));

	buildDecor();
	Indie::Player player(createTexture(_texturesMap[10], {0, 112, 0}, {0, 0, 0}, {0.2f, 0.2f, 0.2f}, true));
	std::vector<Indie::Bomb> bombs;

	_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
	player.setId(waitForId());

	while (m_core.m_device->run() && m_run) {
		processEvents(event);
		m_core.m_driver->beginScene(true, true, color);
		if (event.isKeyDown(irr::KEY_SPACE)) {
			Indie::Bomb bomb(2, 10);
			bomb.setTexture(createTexture(_texturesMap[2], player.getPlayer()->getPosition(), {0, 0, 0}, {100, 100, 100}, false));
			bombs.push_back(bomb);
		}
		bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Indie::Bomb &row) {return row.boom();}), bombs.end());
		readServerInformations();
			// LE CLIENT DOIT DEMANDER AU SERVEUR DE BOUGER
		auto prevPos = player.getPosition();
		player.move(event);
		auto pos = player.getPosition();
		// >> un fct pour envoyer tous les events
		if (static_cast<int>(prevPos.X) != static_cast<int>(pos.X) || static_cast<int>(prevPos.Y) != static_cast<int>(pos.Y) || static_cast<int>(prevPos.Z) != static_cast<int>(pos.Z))
			_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(player.getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z));
		// << un fct pour envoyer tous les events
		m_core.m_sceneManager->drawAll();
		m_core.m_driver->endScene();
		drawCaption(lastFps);
	}
}

const Indie::Core::textureElem &Indie::Core::getTexture(const int &nb)
{
	return _texturesMap[nb];
}