//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Multiplayer
//

#include <Player.hpp>
#include "ManageStrings.hpp"

void Indie::Core::comGameInfos(int event, std::vector<std::string> &infos)
{
	switch (event) {
		case START:
			_state = PLAYING;
			m_state = PLAY;
			_playerObjects.insert(_playerObjects.begin(), std::make_unique<Player>(_playerId, _graphism->createTexture(*_graphism->getTexture(10), {0, _mapper->getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true), _tchat));
			_graphism->resizeNode(_playerObjects[0]->getPlayer(), _mapper->getSize());
			m_core.getCamera().change(m_core.getSceneManager());
			_graphism->buildDecor();
			break;
		case MESSAGE: serverMessage(infos); break;
		default: break;
	}
}

void Indie::Core::comMap(int event, std::vector<std::string> &infos)
{
	switch (event) {
		case APPEAR: _mapper = std::make_unique<Map>(infos, 20.0f, 100.0f, _graphism); break;
		default: break;
	}
}

void Indie::Core::destroyBomb(const irr::core::vector2di &target)
{
	auto &bombs = _graphism->getBombs();

	for (auto elem = bombs.begin() ; elem != bombs.end() ; ++elem) {
		auto &bomb = *elem;
		if (bomb.getPosition2d() == target) {
			bomb.getTexture()->remove();
			bombs.erase(elem);
			return ;
		}
	}
}

void Indie::Core::destroyBlock(const irr::core::vector2di &target)
{
	std::cerr << "DESTROY: X:" << target.X << " et Y:" << target.Y << std::endl;
	auto block = _mapper->get3dBlock(target);
	block->setVisible(false);
	block->setName("");
	auto &map = _mapper->getMap2d();
	map[target.Y][target.X] = 0;
}

void Indie::Core::comPlayer(int event, std::vector<std::string> &infos)
{
	try {
		auto id = std::stoi(infos[0]);

		switch (event) {
			case DEAD: removePlayer(id); break;
			case APPEAR: addPlayer(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stof(infos[4]), std::stof(infos[5])), std::stof(infos[6])); break;
			case MOVE: movePlayer(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stof(infos[4]), std::stof(infos[5])), std::stof(infos[6])); break;
			default: break;
		}
	} catch (const std::exception &e) {}
}

void Indie::Core::comBomb(int event, std::vector<std::string> &infos)
{
	try {
		auto id = std::stoi(infos[0]);

		switch (event) {
			case CREATEBOMB: dropBomb(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stoi(infos[4]), std::stof(infos[5])), std::stoul(infos[6])); break;
			case DESTROYBLOCK: destroyBlock(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1]))); break;
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

void Indie::Core::addPlayer(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos3d, const irr::f32 &rota)
{
	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(id, _graphism->createTexture(*_graphism->getTexture(10), pos3d, {0, 0, 0}, {2, 2, 2}, true), _tchat);
	_graphism->resizeNode(newPlayer->getPlayer(), _mapper->getSize());
	newPlayer->setSpeed(1);
	newPlayer->getPlayer()->setRotation({0, rota, 0});
	newPlayer->setPos2d(pos2d);
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(int id)
{
	if (id == _playerObjects[0]->getId())
		return;
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
		if (p->getId() == id) {
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
	int type, event;

	for (auto &line : servSend) {
		infos = ManageStrings::splitString(line, ':');
		if (infos.size() >= 2 && ManageStrings::isInteger(infos[0]) && ManageStrings::isInteger(infos[1])) {
			type = std::stoi(infos[0]);
			event = std::stoi(infos[1]);
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
	std::cout << "ID: " << id << std::endl;
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