//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// server
//

#include <sstream>
#include <sys/time.h>
#include <vector3d.h>
#include <vector2d.h>
#include <malloc.h>
#include <random>
#include "ManageStrings.hpp"
#include "Server.hpp"

Indie::Server::Server() : _socket(Socket(5567, INADDR_ANY, Indie::Socket::SERVER)), _hostFd(_socket.getFd()), _state(WAITING)
{
	if (_hostFd == -1)
		throw std::runtime_error("Error while creating server socket");
}

void Indie::Server::setClientsFds()
{
	FD_ZERO(&_fdRead);
	FD_SET(_hostFd, &_fdRead);
	for (auto &client : _clients)
		FD_SET(client->_fd, &_fdRead);
}

int Indie::Server::maxFd() const
{
	int max = _hostFd;

	for (auto &client : _clients)
		max = (client->_fd > max ? client->_fd : max);
	return max;
}

void Indie::Server::addClient()
{
	struct sockaddr_in client_sin{};
	socklen_t client_sin_len = sizeof(client_sin);
	std::unique_ptr<Client> newClient = std::make_unique<Client>(_lastId, accept(_hostFd, (struct sockaddr *) &client_sin, &client_sin_len), "Anonymous-" + std::to_string(_lastId + 1));

	dprintf(newClient->_fd, "%d\n", _lastId);
	_clients.push_back(std::move(newClient));
	_lastId += 1;
	for (auto &i : _clients)
		dprintf(i->_fd, "%d:%d:%d\n", GAMEINFOS, EV_UNREADY, _lastId);
}

std::vector<std::vector<int>> Indie::Server::buildMap(const std::string &msg)
{
	std::vector<std::vector<int>> map;
	char *copy = strdup(msg.c_str());
	char *line = strtok(copy, ":");
	auto lineNumberOptimization = 0;

	_map.clear();
	_spawn.clear();
	while (line != nullptr) {
		std::vector<int> tmp;
		std::vector<std::string> oneLine;
		std::string str(line);

		oneLine = ManageStrings::splitString(str, ' ');
		for (auto i = 0 ; static_cast<unsigned>(i) < oneLine.size() ; i++) {
			if (oneLine[i] == "10") {
				_spawn.push_back({i, lineNumberOptimization});
				tmp.push_back(0);
			} else
				tmp.push_back(std::stoi(oneLine[i]));
		}
		map.push_back(tmp);
		line = strtok(nullptr, ":");_map.clear();
		lineNumberOptimization += 1;
	}
	return map;
}

bool Indie::Server::validMove(const int &block)
{
	return ((block == 0) ||
		   (block > FIRE_UP && block < LAST_UP));
}

bool Indie::Server::wallMove(std::unique_ptr<Client> &client, irr::core::vector3df &pos3d, irr::core::vector2di &pos2d, irr::f32 &rotation)
{
	if (rotation == 270 && pos2d.X > 0 && validMove(_map[pos2d.Y][pos2d.X - 1])) {
		client->pos2d.Y = pos2d.Y;
		client->pos2d.X = pos2d.X - 1;
		pos2d.X -= 1;
		pos3d.Z += 20.00f; //taille d'un block, fuck c'est en dur
	} else if (rotation == 90 && pos2d.X < static_cast<int>(_map[pos2d.Y].size() - 1) && validMove(_map[pos2d.Y][pos2d.X + 1])) {
		client->pos2d.Y = pos2d.Y;
		client->pos2d.X = pos2d.X + 1;
		pos2d.X += 1;
		pos3d.Z -= 20.00f; //taille d'un block, fuck c'est en dur
	} else if (rotation == 180 && pos2d.Y < static_cast<int>(_map.size() - 1) && validMove(_map[pos2d.Y + 1][pos2d.X])) {
		client->pos2d.Y = pos2d.Y + 1;
		client->pos2d.X = pos2d.X;
		pos2d.Y += 1;
		pos3d.X -= 20.00f; //taille d'un block, fuck c'est en dur
	} else if (rotation == 0 && pos2d.Y > 0 && validMove(_map[pos2d.Y - 1][pos2d.X])) {
		client->pos2d.Y = pos2d.Y - 1;
		client->pos2d.X = pos2d.X;
		pos2d.Y -= 1;
		pos3d.X += 20.00f; //taille d'un block, fuck c'est en dur
	} else
		return false;
	return true;
}

void Indie::Server::sendInfoToClient()
{
	bool sep = false;
	if (_clients.size() > 1) {
		std::cerr << "To many clients:" << _clients.size() << "cannot save a multiplayer game" << std::endl;
		return;
	}
	std::stringstream ss;
	auto &aClient = _clients[0];

	ss << "";
	/*for (auto &aBot : _bots) {
		if (sep)
			ss << '|';
		ss << "BOT" << ":" <<
		sep = true;
	}*/
	sep = false;
	if (!_bombs.empty()) {
		for (auto &aBomb : _bombs) {
			if (sep)
				ss << '|'; //will be replace by \n in client
			//all ">" will be replace by ":" in client
			ss << "BOMB" << ">" << aBomb->getId() << ">" << aBomb->getState()
			   << ">" << aBomb->getTimeMax() << aBomb->getPower() << ">"
			   << aBomb->getPosition().X << aBomb->getPosition().Y;
			sep = true;
		}
	}
	dprintf(aClient->_fd, "%d:%d:%s\n", GAMEINFOS, INFO, ss.str().c_str());
}

void Indie::Server::comGameInfos(const ObjectsEvents &event, std::vector<std::string> &infos, std::unique_ptr<Client> &client)
{
	(void)infos;
	std::cout << "Game - Event: " << event << " - \"" << _lastCmd << "\"\n";
	switch (event) {
		case EV_READY:
			client->_state = PLAYING;
			for (auto &i : _clients)
				dprintf(i->_fd, "%d:%d:%d\n", GAMEINFOS, event, client->_id);
			break;
		case EV_UNREADY:
			client->_state = WAITING;
			for (auto &i : _clients)
				dprintf(i->_fd, "%d:%d:%d\n", GAMEINFOS, event, client->_id);
			break;
		case MESSAGE:
			for (auto &i : _clients)
				dprintf(i->_fd, "1:4:%s: %s", client->_name.c_str(), &_lastCmd[4]);
			break;
		case INFO: sendInfoToClient(); break;
		default: break;
	}
}

void Indie::Server::createBomb(std::unique_ptr<Client> &client, irr::core::vector2di pos2d, std::size_t power, std::size_t limit)
{
	std::size_t elem = 0;
	for (auto bomb = _bombs.begin() ; elem < limit && bomb != _bombs.end() ; ++bomb)
		if ((*bomb)->getId() == client->_id)
			++elem;
	if (elem < limit && getBlock(pos2d) == 0) {
		_bombs.push_back(std::make_unique<Indie::Bomb>(2, power, pos2d, client->_id));
		setBlock(pos2d, 3);
		for (auto &i : _clients)
			dprintf(i->_fd, "%s\n", _lastCmd.c_str());
	}
}

void Indie::Server::comBomb(const ObjectsEvents &event, std::vector<std::string> &infos, std::unique_ptr<Client> &client)
{
	/*std::cout << "Bomb - Event: " << event << " - \"" << _lastCmd << "\"\n";*/

	switch (event) {
		case CREATEBOMB: {
			createBomb(client, {std::stoi(infos[1]), std::stoi(infos[2])}, std::stoul(infos[6]), std::stoul(infos[7]));
			break;
		}
		default: break;
	}
}

void Indie::Server::comPlayer(const ObjectsEvents &event, std::vector<std::string> &infos, std::unique_ptr<Client> &client)
{
/*	std::cout << "Player - Event: " << event << " - \"" << _lastCmd << "\"\n";*/

	switch (event) {
		case STAND : {
			auto id = std::stoi(infos[0]);
			for (auto &i : _clients)
				if (id != i->_id)
					dprintf(i->_fd, "%d:%d:%d\n", PLAYER, event, id);
			break ;
		}
		case MOVE: {
			irr::core::vector2di position2d(std::stoi(infos[1]), std::stoi(infos[2]));
			irr::core::vector3df position3d(std::stof(infos[3]), std::stof(infos[4]), std::stof(infos[5]));
			irr::f32 rotation = std::stof(infos[6]);
			auto wallUp = static_cast<bool>(std::stoi(infos[7]));
			if (_map[position2d.Y][position2d.X] == 8 && wallUp) {
				if (wallMove(client, position3d, position2d, rotation))
					for (auto &i : _clients)
						dprintf(i->_fd, "%d:%d:%d:%d:%d:%f:%f:%f:%f:%i\n", PLAYER, event, client->_id, position2d.X, position2d.Y, position3d.X, position3d.Y, position3d.Z, rotation, wallUp);
			} else if ((getBlock(client->pos2d) == 1 && getBlock(position2d) == 3) /* sinon on reste bloqué contre le mur*/
				|| (getBlock(client->pos2d) == 3)
				|| (getBlock(position2d) == 0)) /*normal*/{
				client->pos2d = position2d;
				for (auto &i : _clients)
					dprintf(i->_fd, "%d:%d:%d:%d:%d:%f:%f:%f:%f:%i\n", PLAYER, event, client->_id, position2d.X, position2d.Y, position3d.X, position3d.Y, position3d.Z, rotation, wallUp);
			} else if (getBlock(position2d) > FIRST_UP && getBlock(position2d) < LAST_UP) {
				client->pos2d = position2d;
				for (auto &i : _clients)
					dprintf(i->_fd, "%d:%d:%d:%d:%d\n", MAP, TAKEBONUS, position2d.X, position2d.Y, getBlock(position2d));
				setBlock(position2d, 0);
			}
			break;
		}
		case LEAVE: {
			auto pos = std::find(_clients.begin(), _clients.end(), client);

			if (pos != _clients.end()) {
				pos->reset();
				_clients.erase(pos);
			}
		}
		default: break;
	}
}

void Indie::Server::comMap(const ObjectsEvents &event, std::vector<std::string> &infos, std::unique_ptr<Client> &client)
{
	(void)infos;
	(void)client;
	std::cout << "Map - Event: " << event << " - \"" << _lastCmd << "\"\n";
	switch (event) {
		case APPEAR:
			_map = buildMap(&_lastCmd[4]);
			_mapMsg = std::string(ManageStrings::replaceStr("10", "00", _lastCmd));
		default: break;
	}
}

int Indie::Server::readClient(std::unique_ptr<Client> &client)
{
	static char buffer[8192];
	char *tmp = nullptr;
	ssize_t size;
	std::vector<std::string> infos;
	ObjectsType type;
	ObjectsEvents event;

	size = read(client->_fd, buffer, 8192);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp) {
			_lastCmd = std::string(tmp);
			infos = ManageStrings::splitString(_lastCmd, ':');
			type = static_cast<ObjectsType>(std::stoi(infos[0]));
			event = static_cast<ObjectsEvents>(std::stoi(infos[1]));
			infos.erase(infos.begin(), infos.begin() + 2);
			(this->*_objectsFct[type])(event, infos, client);
			tmp = strtok(nullptr, "\n");
		}
		return 0;
	}
	auto pos = std::find(_clients.begin(), _clients.end(), client);

	if (pos != _clients.end()) {
		pos->reset();
		_clients.erase(pos);
	}
	for (auto &aClient : _clients)
		dprintf(aClient->_fd, "0:1:%d\n", aClient->_id);
	return 1;
}

void Indie::Server::readOnFds()
{
	struct timeval tv = {0, 200};

	if (select(maxFd() + 1, &_fdRead, nullptr, nullptr, &tv) == -1)
		throw std::runtime_error("Error while reading server socket");
	if (FD_ISSET(_hostFd, &_fdRead))
		addClient();
	for (unsigned i = 0; i < _clients.size(); i++) {
		if (FD_ISSET(_clients[i]->_fd, &_fdRead))
			i = (readClient(_clients[i]) == 1 ? i - 1 : i);
	}
}

Indie::GameState Indie::Server::checkIfStartGame()
{
	std::size_t spawnId = 0;

	if (_clients.empty())
		return WAITING;
	for (auto &client : _clients) {
		if (client->_state == WAITING)
			return WAITING;
	}
	for (auto &client : _clients) {
		dprintf(client->_fd, "%s\n", _mapMsg.c_str()); // ENVOI DE LA CARTE
		dprintf(client->_fd, "1:3\n"); // CODE POUR GAME START
		client->pos2d = irr::core::vector2di(_spawn[spawnId][0], _spawn[spawnId][1]);
		spawnId = (spawnId + 1) % _spawn.size();
	}

	// On donne la pos de chaque joueur
	for (auto &client : _clients) {
		dprintf(client->_fd, "0:0:%d:%d:%d\n", client->_id, client->pos2d.X, client->pos2d.Y);
		for (auto &pop : _clients) {
			if (pop != client)
				dprintf(client->_fd, "0:0:%d:%d:%d\n", pop->_id, pop->pos2d.X, pop->pos2d.Y);
		}
	}
	return PLAYING;
}

bool Indie::Server::hitPlayer(const irr::core::vector2di &target, const int &id)
{
	for (auto &aClient : _clients) {
		if (aClient->_alive && aClient->pos2d.X == target.X && aClient->pos2d.Y == target.Y) {
			std::cerr << "player hit" << std::endl;
			aClient->_alive = false;
			auto state = aClient->_id == id ? SUICIDE : DEAD;
			for (auto &toaClient : _clients)
				dprintf(toaClient->_fd, "%d:%d:%d\n", PLAYER, state, aClient->_id);
			return true;
		}
	}
	return false;
}

void Indie::Server::replaceByBonus(const irr::core::vector2di &pos)
{
	auto bonus = LAST_UP;
	static std::default_random_engine generator;
	std::uniform_int_distribution<int> random(0, 4);
	std::uniform_int_distribution<int> distribution(FIRST_UP + 1, LAST_UP - 1);
	if (random(generator) > 0)
		bonus = static_cast<PowerUpType>(distribution(generator));

	if (_map[pos.Y][pos.X] != 1 || bonus == LAST_UP) {
		_map[pos.Y][pos.X] = 0;
		for (auto &aClient : _clients)
			dprintf(aClient->_fd, "%d:%d:%d:%d\n", MAP, DESTROYBLOCK, pos.X, pos.Y);
	} else {
		_map[pos.Y][pos.X] = static_cast<int>(bonus);
		for (auto &aClient : _clients)
			dprintf(aClient->_fd, "%d:%d:%d:%d:%d\n", MAP, CREATEBLOCK, bonus, pos.X, pos.Y);
	}
}

void Indie::Server::destroyEntities(std::unique_ptr<Indie::Bomb> &bomb)
{
	auto pos2d = bomb->getPosition();
	auto power = static_cast<int>(bomb->getPower());

	if (!hitPlayer(irr::core::vector2di(pos2d.X, pos2d.Y), bomb->getId())) {
		for (int pos = 1; pos <= power; ++pos) {
			if (hitPlayer(irr::core::vector2di(pos2d.X + pos, pos2d.Y), bomb->getId())) {
				break;
			} else if (_map[pos2d.Y][pos2d.X + pos] == 8) {
				break;
			} else if (pos2d.X + pos <
					   static_cast<int>(_map[pos2d.Y].size() - 1) &&
					   _map[pos2d.Y][pos2d.X + pos] != 0) {
				replaceByBonus(irr::core::vector2di(pos2d.X + pos, pos2d.Y));
				break;
			}
		}

		for (int pos = 1; pos <= power && pos2d.X - pos > 0; ++pos) {
			if (hitPlayer(irr::core::vector2di(pos2d.X - pos, pos2d.Y), bomb->getId())) {
				break;
			} else if (_map[pos2d.Y][pos2d.X - pos] == 8) {
				break;
			} else if (_map[pos2d.Y][pos2d.X - pos] != 0) {
				replaceByBonus(irr::core::vector2di(pos2d.X - pos, pos2d.Y));
				break;
			}
		}

		for (int pos = 1; pos <= power; ++pos) {
			if (hitPlayer(irr::core::vector2di(pos2d.X, pos2d.Y + pos), bomb->getId())) {
				break;
			} else if (_map[pos2d.Y + pos][pos2d.X] == 8) {
				break;
			} else if (pos2d.Y + pos < static_cast<int>(_map.size() - 1) &&
					   _map[pos2d.Y + pos][pos2d.X] != 0) {
				replaceByBonus(irr::core::vector2di(pos2d.X, pos2d.Y + pos));
				break;
			}
		}

		for (int pos = 1; pos <= power && pos2d.Y - pos > 0; ++pos) {
			if (hitPlayer(irr::core::vector2di(pos2d.X, pos2d.Y - pos), bomb->getId())) {
				break;
			} else if (_map[pos2d.Y - pos][pos2d.X] == 8) {
				break;
			} else if (_map[pos2d.Y - pos][pos2d.X] != 0) {
				replaceByBonus(irr::core::vector2di(pos2d.X, pos2d.Y - pos));
				break;
			}
		}
	}
	for (auto &aClient : _clients)
		dprintf(aClient->_fd, "%d:%d:%i:%i\n", BOMB, DESTROYBOMB, pos2d.X, pos2d.Y);
}


void Indie::Server::manageBomb()
{
	auto elem = _bombs.begin();

	while (elem != _bombs.end()) {
		auto &bomb = *elem;
		bomb->tictac();
		if (bomb->getState() == Indie::Bomb::BOOM) {
			destroyEntities(bomb);
			_map[bomb->getPosition().Y][bomb->getPosition().X] = 0;
			_bombs.erase(elem);
			elem = _bombs.begin();
		} else
			++elem;
	}
}

void Indie::Server::start()
{
	// GERER LA DESTRUCTION DU SALON (tlm quitte / partie terminée etc..)
	_objectsFct.push_back(&Indie::Server::comPlayer);
	_objectsFct.push_back(&Indie::Server::comGameInfos);
	_objectsFct.push_back(&Indie::Server::comMap);
	_objectsFct.push_back(&Indie::Server::comBomb);
	_lastId = 0;
	while (true) {
		manageBomb();
		if (_state == WAITING)
			_state = checkIfStartGame();
		setClientsFds();
		readOnFds();
		if (_state == PLAYING and _clients.empty())
			break;
	}
	_socket.closeSocket();
}

void Indie::Server::runServer()
{
	try {
		auto server = Indie::Server();
		server.start();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

bool Indie::operator!=(std::unique_ptr<Indie::Client> &lhs,
					   std::unique_ptr<Indie::Client> &rhs)
{
	return !(lhs->_id == rhs->_id && lhs->_fd == rhs->_fd &&
			 lhs->_name == rhs->_name);
}

bool Indie::operator==(std::unique_ptr<Indie::Client> &lhs,
					   std::unique_ptr<Indie::Client> &rhs)
{
	return (lhs->_id == rhs->_id && lhs->_fd == rhs->_fd &&
			lhs->_name == rhs->_name);
}