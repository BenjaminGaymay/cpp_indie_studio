//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Multiplayer
//

#include <Player.hpp>
#include "ManageStrings.hpp"

void Indie::Core::addPlayer(int id, irr::core::vector3df &pos, const irr::f32 &rota)
{
	std::cout << "Add player: " << id << std::endl;
	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(id, _graphism->createTexture(
					*_graphism->getTexture(10), pos, {0, 0, 0}, {2, 2, 2}, true));
	_graphism->resizeNode(newPlayer->getPlayer(), _mapper->getSize());
	newPlayer->setSpeed(1);
	newPlayer->getPlayer()->setRotation({0, rota, 0});
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(int id, irr::core::vector3df &pos, const irr::f32 &rota)
{
	(void)pos;
	(void)rota;
	if (id == _playerObjects[0]->getId())
		return;
	for (auto &p : _playerObjects) {
		if (p->getId() == id) {
			auto pPos = std::find(_playerObjects.begin(), _playerObjects.end(), p);
			pPos->reset();
			_playerObjects.erase(pPos);
			return;
		}
	}
}

void Indie::Core::movePlayer(int id, irr::core::vector3df &pos, const irr::f32 &rota)
{
	for (auto &p : _playerObjects)
		if (p->getId() == id) {
			if (p->isStanding())
				p->getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
			p->setStanding(false);
			p->getPlayer()->setRotation({0, rota, 0});
			p->setPosition(pos);
			return;
		}
}

void Indie::Core::readServerInformations(std::vector<std::string> servSend)
{
	std::vector<std::string> info;
	int type, event, id;
	irr::f32 rota;

	for (auto &line : servSend) {
		info = ManageStrings::splitString(line, ':');
		if (!info.empty()) {
			// >> SECURISER ÇA
			type = std::stoi(info[0]);
			event = std::stoi(info[1]);
			if (type == GAMEINFOS && event == START) {
				_state = PLAYING;
				m_state = PLAY;
				_mapper = std::make_unique<Map>("assets/maps/map.txt", 20.0f, 100.0f, _graphism);
				_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(_playerId, _graphism->createTexture(*_graphism->getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true)));
				_graphism->resizeNode(_playerObjects[0]->getPlayer(), _mapper->getSize());
				m_core.getCamera().change(m_core.getSceneManager());				_graphism->buildDecor();
			}
			else {
				id = std::stoi(info[2]);

				irr::core::vector3df pos(std::stof(info[3]), std::stof(info[4]), std::stof(info[5]));
				rota = std::stof(info[6]);
			// <<
				switch (type) {
					case Indie::PLAYER:
						(this->*_playersFct[event])(id, pos, rota); break;
					default:break;
				}
			}
		}
	}
}

int Indie::Core::waitForId()
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
	readServerInformations(servSend);
	return id;
}
