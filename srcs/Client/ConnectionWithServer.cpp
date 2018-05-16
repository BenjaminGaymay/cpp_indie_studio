/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Multiplayer
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

void Indie::Core::addPlayer(Indie::Graphism &graphism, int id, irr::core::vector3df &pos)
{
	std::cout << "Add player: " << id << std::endl;
	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(id, graphism.createTexture(*graphism.getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true));
	graphism.resizeNode(newPlayer->getPlayer(), _mapper->getSize());
	newPlayer->setSpeed(1);
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(Indie::Graphism &graphism, int id, irr::core::vector3df &pos)
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
	std::cout << "ID: " << id << std::endl;
	servSend.erase(servSend.begin());
	readServerInformations(servSend, graphism);
	return id;
}
