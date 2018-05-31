//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// server
//

#include <sys/time.h>
#include <irrlicht/vector3d.h>
#include <irrlicht/vector2d.h>
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
	static int id = 0;
	struct sockaddr_in client_sin{};
	socklen_t client_sin_len = sizeof(client_sin);
	std::unique_ptr<Client> newClient = std::make_unique<Client>(id, accept(_hostFd, (struct sockaddr *) &client_sin, &client_sin_len), "Anonymous-" + std::to_string(id + 1));

	dprintf(newClient->_fd, "%d\n", id);
	_clients.push_back(std::move(newClient));
	id += 1;
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
	free(copy);
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
	} else if (rotation == 90 && pos2d.X < static_cast<int>(_map[pos2d.Y].size()) && validMove(_map[pos2d.Y][pos2d.X + 1])) {
		client->pos2d.Y = pos2d.Y;
		client->pos2d.X = pos2d.X + 1;
		pos2d.X += 1;
		pos3d.Z -= 20.00f; //taille d'un block, fuck c'est en dur
	} else if (rotation == 180 && pos2d.Y < static_cast<int>(_map.size()) && validMove(_map[pos2d.Y + 1][pos2d.X])) {
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

int Indie::Server::readClient(std::unique_ptr<Client> &client)
{
	static char buffer[8192];
	char *tmp = nullptr;
	ssize_t size;

	size = read(client->_fd, buffer, 8192);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp) {
			std::cout << "Client " << client->_id << " say " << tmp
					  << std::endl;
			if (std::string(tmp) == "READY") {
				client->_state = PLAYING;
				break;
			}
			else if (std::string(tmp) == "UNREADY") {
				client->_state = WAITING;
				break;
			}
			// >> reception map
			if (std::string(tmp).compare(0, 4, "2:0:") == 0) {
				_map = buildMap(&tmp[4]);
				_mapMsg = std::string(ManageStrings::replaceStr("10", "00", tmp));
			}
			// <<
			if (_state == WAITING)
				return 0;
			std::string cmd = tmp;
			auto enumType = std::stoi(strsep(&tmp, ":")); //PLAYER
			auto enumEvent = std::stoi(strsep(&tmp, ":")); //MOVE
			if (enumType == BOMB && enumEvent == CREATEBOMB) {
				auto enumId = std::stoi(strsep(&tmp, ":"));
				irr::core::vector2di position2d;
				position2d.X = std::stoi(strsep(&tmp, ":"));
				position2d.Y = std::stoi(strsep(&tmp, ":"));
				irr::core::vector3df position3d;
				position3d.X = std::stof(strsep(&tmp, ":"));
				position3d.Y = std::stof(strsep(&tmp, ":"));
				position3d.Z = std::stof(strsep(&tmp, ":"));
				std::size_t power = std::stoul(strsep(&tmp, ":"));
				std::size_t limit = std::stoul(strsep(&tmp, ":"));
				(void) position3d;
				(void) enumId;
				std::cerr << "BOMB CREATION: POWER:" << power << " X:" << position2d.X << " et Y:" << position2d.Y << std::endl;
				std::size_t elem = 0;
				for (auto bomb = _bombs.begin() ; elem < limit && bomb != _bombs.end() ; ++bomb)
					if ((*bomb)->getId() == client->_id)
						++elem;
				if (elem < limit && _map[position2d.Y][position2d.X] == 0) {
					_bombs.push_back(std::make_unique<Indie::Bomb>(2, power, position2d, client->_id));
					_map[position2d.Y][position2d.X] = 3;
					for (auto &i : _clients)
						dprintf(i->_fd, cmd.c_str());
				}
			} else if (enumType == PLAYER && enumEvent == MOVE) {
				auto enumId = std::stoi(strsep(&tmp, ":"));
				irr::core::vector2di position2d;
				position2d.X = std::stoi(strsep(&tmp, ":"));
				position2d.Y = std::stoi(strsep(&tmp, ":"));
				irr::core::vector3df position3d;
				position3d.X = std::stof(strsep(&tmp, ":"));
				position3d.Y = std::stof(strsep(&tmp, ":"));
				position3d.Z = std::stof(strsep(&tmp, ":"));
				irr::f32 rotation = std::stof(strsep(&tmp, ":"));
				bool wallUp = static_cast<bool>(std::stoi(strsep(&tmp, ":")));
				(void) position3d;
				(void) enumId;
				if (_map[position2d.Y][position2d.X] == 8 && wallUp) {
					if (wallMove(client, position3d, position2d, rotation))
						for (auto &i : _clients)
							dprintf(i->_fd, "%d:%d:%d:%d:%d:%f:%f:%f:%f:%i\n", enumType, enumEvent, client->_id, position2d.X, position2d.Y, position3d.X, position3d.Y, position3d.Z, rotation, wallUp);
				} else if ((_map[client->pos2d.Y][client->pos2d.X] == 1 && _map[position2d.Y][position2d.X] == 3) /* sinon on reste bloqué contre le mur*/
					|| (_map[client->pos2d.Y][client->pos2d.X] == 3)
					|| (_map[position2d.Y][position2d.X] == 0)) /*normal*/{
					client->pos2d.Y = position2d.Y;
					client->pos2d.X = position2d.X;
					for (auto &i : _clients)
						dprintf(i->_fd, "%d:%d:%d:%d:%d:%f:%f:%f:%f:%i\n", enumType, enumEvent, client->_id, position2d.X, position2d.Y, position3d.X, position3d.Y, position3d.Z, rotation, wallUp);
				} else if (_map[position2d.Y][position2d.X] > FIRST_UP && _map[position2d.Y][position2d.X] < LAST_UP) {
					client->pos2d.Y = position2d.Y;
					client->pos2d.X = position2d.X;
					for (auto &i : _clients)
						dprintf(i->_fd, "%d:%d:%d:%d:%d\n", MAP, TAKEBONUS, position2d.X, position2d.Y, _map[position2d.Y][position2d.X]);
					_map[position2d.Y][position2d.X] = 0;
					}
			} else {
				for (auto &i : _clients) {
					if (std::string(cmd).compare(0, 4, "1:4:") == 0)
						// Renvoyer les msg dans le menu d'attente
						dprintf(i->_fd, "1:4:%s: %s",
								client->_name.c_str(), &cmd[4]);
				}
			}


			tmp = strtok(nullptr, "\n");
		}
		return 0;
	}
	std::cout << "Client " << client->_id << " out" << std::endl;
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
		std::cout << "Envoi de la carte\n";
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

bool Indie::Server::hitPlayer(const irr::core::vector2di &target)
{
	(void) target;
	/*for (auto &aClient : _clients) {
		if (aClient->pos2d.X == target.X && aClient->pos2d.Y == target.Y) {
			dprintf(aClient->_fd, "%d:%d:%d\n", PLAYER, DEAD, aClient->_id);
			return true;
		}
	}*/
	return false;
}

void Indie::Server::replaceByBonus(const irr::core::vector2di &pos)
{
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution(FIRST_UP + 1, LAST_UP);
	auto bonus = static_cast<PowerUpType>(distribution(generator));

	std::cerr << "bonus généré:" << bonus << std::endl;
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

	for (int pos = 1 ; pos <= power ; ++pos) {
		if (hitPlayer(irr::core::vector2di(pos2d.X + pos, pos2d.Y))) {
			break;
		} else if (_map[pos2d.Y][pos2d.X + pos] == 8) {
			break;
		} else if (pos2d.X + pos < static_cast<int>(_map[pos2d.Y].size() - 1)
				 && _map[pos2d.Y][pos2d.X + pos] != 0) {
			replaceByBonus(irr::core::vector2di(pos2d.X + pos, pos2d.Y));
			break;
		}
	}

	for (int pos = 1 ; pos <= power && pos2d.X - pos > 0; ++pos) {
		if (hitPlayer(irr::core::vector2di(pos2d.X - pos, pos2d.Y))) {
			break;
		} else if (_map[pos2d.Y][pos2d.X - pos] == 8) {
			break;
		} else if (_map[pos2d.Y][pos2d.X - pos] != 0) {
			replaceByBonus(irr::core::vector2di(pos2d.X - pos, pos2d.Y));
			break;
		}
	}

	for (int pos = 1 ; pos <= power ; ++pos) {
		if (hitPlayer(irr::core::vector2di(pos2d.X, pos2d.Y + pos))) {
			break;
		} else if (_map[pos2d.Y + pos][pos2d.X] == 8) {
				break ;
		} else if (pos2d.Y + pos < static_cast<int>(_map.size() - 1) && _map[pos2d.Y + pos][pos2d.X] != 0) {
			replaceByBonus(irr::core::vector2di(pos2d.X, pos2d.Y + pos));
			break;
		}
	}

	for (int pos = 1 ; pos <= power && pos2d.Y - pos > 0; ++pos) {
		if (hitPlayer(irr::core::vector2di(pos2d.X, pos2d.Y - pos))) {
			break;
		} else if (_map[pos2d.Y - pos][pos2d.X] == 8) {
				break ;
		} else if (_map[pos2d.Y - pos][pos2d.X] != 0) {
			replaceByBonus(irr::core::vector2di(pos2d.X, pos2d.Y - pos));
			break;
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
	while (1) {
		manageBomb();
		if (_state == WAITING)
			_state = checkIfStartGame();
		setClientsFds();
		readOnFds();
	}
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