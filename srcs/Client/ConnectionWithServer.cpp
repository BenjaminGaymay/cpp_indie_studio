//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Multiplayer
//

#include <Player.hpp>
#include "ManageStrings.hpp"

void Indie::Core::comGameInfos(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	switch (event) {
		case START:
			_state = PLAYING;
			m_state = PLAY;
			m_menu.m_ready->setVisible(false);
			m_core.m_device->getCursorControl()->setVisible(false);
			m_core.getCamera().change(m_core.getSceneManager(), Camera::FPS);
			_graphism->buildDecor();
			break;
		case MESSAGE: serverMessage(infos); break;
		default: break;
	}
}

void Indie::Core::comMap(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	switch (event) {
		case APPEAR: _mapper = std::make_unique<Map>(infos, 20.0f, 100.0f, _graphism); break;
		case DESTROYBLOCK: destroyBlock(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1]))); break;
		case CREATEBLOCK: createBlock(static_cast<PowerUpType>(std::stoi(infos[0])), irr::core::vector2di(std::stoi(infos[1]), std::stoi(infos[2]))); break;
		case TAKEBONUS: takeBonus(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1])), static_cast<PowerUpType >(std::stoi(infos[2]))); break;
		default: break;
	}
}

void Indie::Core::takeBonus(const irr::core::vector2di &pos, const PowerUpType &bonus)
{
	_engine->play2D("music/bonus.wav", false, false, false);
	std::cerr << "J'ai pris un bonus:" << bonus << std::endl;
	switch (bonus) {
		case SPEED_UP : _playerObjects[0]->setSpeed(_playerObjects[0]->getSpeed() + 0.1f); std::cerr << "SPEEDUP" << std::endl; break ;
		case BOMB_UP : _playerObjects[0]->setBombNumber(_playerObjects[0]->getBombNumber() + 1); std::cerr << "BOMBUP" << std::endl; break;
		case FIRE_UP : _playerObjects[0]->setPower(_playerObjects[0]->getPower() + 1); std::cerr << "FIREUP" << std::endl; break ;
		case WALLPASS_UP : _playerObjects[0]->setWallUp(true) ; std::cerr << "WALLUP" << std::endl; break ;
		default: std::cerr << "DEFAULT:" << bonus << std::endl; break ;
	}
	findAndDestroyEntity(pos);
}

void Indie::Core::createBlock(const Indie::PowerUpType &bonus, const irr::core::vector2di &pos)
{
	destroyBlock(pos);
	auto block = _mapper->get3dBlock(pos);
	auto bonusBlock = _graphism->createTexture(*_graphism->getTexture(bonus), block->getPosition(), {0, 0, 0}, {2, 2 , 2}, true);
	_graphism->resizeNode(bonusBlock, _mapper->getSize());
	_graphism->getBonus().emplace_back(pos, bonusBlock);
}

bool Indie::Core::findAndDestroyEntity(const irr::core::vector2di &target)
{
	for (auto elem = _graphism->getBonus().begin() ; elem != _graphism->getBonus().end() ; ++elem) {
		auto &bonus = *elem;
		if (bonus.getPosition2d() == target) {
			bonus.getTexture()->remove();
			_graphism->getBonus().erase(elem);
			return true;
		}
	};
	return false;
}

void Indie::Core::destroyBlock(const irr::core::vector2di &target)
{
	auto &map = _mapper->getMap2d();
	map[target.Y][target.X] = 0;
	if (findAndDestroyEntity(target))
		return ;
	auto block = _mapper->get3dBlock(target);
	block->setVisible(false);
	block->setName("");
}

void Indie::Core::destroyBomb(const irr::core::vector2di &target)
{
	auto &bombs = _graphism->getBombs();

	for (auto elem = bombs.begin() ; elem != bombs.end() ; ++elem) {
		auto &bomb = *elem;
		if (bomb.getPosition2d() == target) {
			_engine->play2D("music/boom.wav", false, false, false);
			bomb.getTexture()->remove();
			bombs.erase(elem);
			return ;
		}
	}
}

void Indie::Core::comPlayer(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	try {
		auto id = std::stoi(infos[0]);

		switch (event) {
			case DEAD: removePlayer(id); break;
			case APPEAR: addPlayer(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2]))); break;
			case MOVE: movePlayer(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stof(infos[4]), std::stof(infos[5])), std::stof(infos[6])); break;
			default: break;
		}
	} catch (const std::exception &e) {}
}

void Indie::Core::comBomb(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	try {
		auto id = std::stoi(infos[0]);

		switch (event) {
			case CREATEBOMB: dropBomb(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stoi(infos[4]), std::stof(infos[5])), std::stoul(infos[6])); break;
			case DESTROYBOMB: destroyBomb(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1]))); break;
			default: break;
		}
	} catch (const std::exception &e) {}
}

void Indie::Core::dropBomb(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos3d, const std::size_t &power)
{
	(void) id;
	(void) pos2d;
	(void) power;
	auto block = _mapper->get3dBlock(pos3d + _mapper->getSize() / 2);
	auto bomb = _graphism->createTexture(*_graphism->getTexture(3), block->getPosition(), {0, 0, 0}, {2, 2, 2}, true);
	_graphism->resizeNode(bomb, _mapper->getSize());
	_graphism->getBombs().emplace_back(pos2d, bomb);

}

void Indie::Core::addPlayer(int id, const irr::core::vector2di &pos2d)
{
	auto pos3d = _mapper->get3dBlock(pos2d)->getPosition();

	std::cout << pos3d.X << ":" << pos3d.Y << ":" << pos3d.Z << std::endl;
	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(id, static_cast<irr::scene::IAnimatedMeshSceneNode *>(_graphism->createTexture(*_graphism->getTexture(10), pos3d, {0, 0, 0}, {2, 2, 2}, true)), _tchat);
	_graphism->resizeNode(newPlayer->getPlayer(), _mapper->getSize());
	newPlayer->setSpeed(1);
	newPlayer->setPos2d(pos2d);
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(int id)
{
	if (id == _playerObjects[0]->getId()) { //joueur principale meurt, bha faut gérer
		_engine->play2D("music/suicide.wav", false, false, false);
		_playerObjects[0]->getPlayer()->remove();
		_playerObjects[0]->setAlive(false); //#BENOIT tu dois quitter proprement
		m_state = SPEC;
		return;
	}
	for (auto &p : _playerObjects) {
		if (p->getId() == id) {
			p->getPlayer()->remove();
			auto pPos = std::find(_playerObjects.begin(), _playerObjects.end(), p);
			pPos->reset();
			_playerObjects.erase(pPos);
			return;
		}
	}
}

void Indie::Core::movePlayer(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos, const irr::f32 &rota)
{
	for (auto &p : _playerObjects)
		if (p->getId() == id && p->isAlive()) {
			if (p->isStanding())
				p->getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
			p->setStanding(false);
			p->getPlayer()->setRotation({0, rota, 0});
			p->setPosition(pos);
			p->setPos2d(pos2d);
			return;
		}
}

void Indie::Core::serverMessage(const std::vector<std::string> &message)
{
	std::string msg;

	for (auto &line : message)
		msg += line + ":";
	msg[msg.size() - 1] = '\0';
	_tchat._messages.push_back(msg);

	if (_tchat._messages.size() > 5)
		_tchat._messages.erase(_tchat._messages.begin(), _tchat._messages.end() - 5);
}

void Indie::Core::readServerInformations(std::vector<std::string> servSend)
{
	std::vector<std::string> infos;
	ObjectsType type;
	ObjectsEvents event;

	for (auto &line : servSend) {
		infos = ManageStrings::splitString(line, ':');
		if (infos.size() >= 2 && ManageStrings::isInteger(infos[0]) && ManageStrings::isInteger(infos[1])) {
			type = static_cast<ObjectsType>(std::stoi(infos[0]));
			event = static_cast<ObjectsEvents>(std::stoi(infos[1]));
			infos.erase(infos.begin(), infos.begin() + 2);
			(this->*_objectsFct[type])(event, infos);
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
	servSend.erase(servSend.begin());
	readServerInformations(servSend);
	return id;
}

void Indie::Core::sendMapToServer(const std::string &path)
{
	std::string map;
	FILE *file = fopen(path.c_str(), "r");
	char *buffer = nullptr;
	std::size_t size = 0;

	if (!file)
		throw std::runtime_error("Error: can't open map.");
	while (getline(&buffer, &size, file) > 0) {
		buffer[strlen(buffer) - 1] = '\0';
		map += std::string(buffer) + ":";
	}
	dprintf(_socket->getFd(), "2:0:%s\n", map.c_str());
	free(buffer);
	fclose(file);
}