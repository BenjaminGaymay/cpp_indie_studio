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
#include "Graphism.hpp"
#include "ManageStrings.hpp"

void Indie::Core::addPlayer(Indie::Graphism &core, int id, irr::core::vector3df &pos)
{
	std::cout << "Add player: " << id << std::endl;
	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(id, core.createTexture(*core.getTexture(10), pos, {0, 0, 0}, {0.2f, 0.2f, 0.2f}, true));
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(Indie::Graphism &core, int id, irr::core::vector3df &pos)
{
	for (auto &p : _playerObjects) {
		if (p->getId() == id) {
			auto pos = std::find(_playerObjects.begin(), _playerObjects.end(), p);
			pos->reset();
			_playerObjects.erase(pos);
			return;
		}
	}
}

void Indie::Core::movePlayer(Indie::Graphism &core, int id, irr::core::vector3df &pos)
{
	for (auto &p : _playerObjects)
		if (p->getId() == id) {
			std::cout << "Player: " << id << " move" << std::endl;
			if (p->isStanding())
				p->getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
			p->setStanding(false);
			p->rotationWithMove(p->getPlayer(), pos);
			p->setPosition(pos);
			return;
		}
}

Indie::Core::Core()
{
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

int Indie::Core::waitForId(Indie::Graphism &graphism)
{
	std::vector<std::string> servSend;
	int id;

	while (servSend.empty())
		servSend = _socket->readSocket();
	for (auto &c : servSend[0])
		if (!isdigit(c))
			throw std::runtime_error("Communication error");

	id = std::stoi(servSend[0]);
	servSend.erase(servSend.begin());
	readServerInformations(servSend, graphism);
	return id;
}

void Indie::Core::readServerInformations(std::vector<std::string> &servSend, Indie::Graphism &graphism)
{
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
					(this->*_playersFct[event])(graphism, id, pos); break;
				default:break;
			}
		}
	}
}


void Indie::Core::run()
{
	Events event;
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);
	std::vector<std::string> servSend;
	m_core.initWindow(event);
	m_run = true;
	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0, 255.0, 255.0));
	Graphism graphism(m_core);
	graphism.buildDecor();
	Map map(20.00f, 100.00f);
	map.initMap("assets/maps/map2.txt");
	map.load(graphism);
	m_splash.display(m_core.m_device);

	_socket = std::make_unique<Socket>(5567, "127.0.0.1", Indie::Socket::CLIENT);
	_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(waitForId(graphism), graphism.createTexture(*graphism.getTexture(10), {0, 112, 0}, {0, 0, 0}, {0.2f, 0.2f, 0.2f}, true)));

	while (m_core.m_device->run() && m_run) {
		processEvents(event);
		m_core.m_driver->beginScene(true, true, color);
		servSend = _socket->readSocket();
		readServerInformations(servSend, graphism);
			// LE CLIENT DOIT DEMANDER AU SERVEUR DE BOUGER
		auto prevPos = _playerObjects[0]->getPosition();
		auto pos = _playerObjects[0]->move(event);
		// >> un fct pour envoyer tous les events ?
		if (prevPos.X != pos.X || prevPos.Y != pos.Y || prevPos.Z != pos.Z)
			_socket->sendInfos(Indie::PLAYER, Indie::MOVE, std::to_string(_playerObjects[0]->getId()) + ':' + std::to_string(pos.X) + ':' + std::to_string(pos.Y) + ':' + std::to_string(pos.Z));
		// << un fct pour envoyer tous les events ?
		m_core.m_sceneManager->drawAll();
		m_core.m_driver->endScene();
		drawCaption(lastFps);
	}
}