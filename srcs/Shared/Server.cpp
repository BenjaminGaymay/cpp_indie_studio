//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// server
//

#include <sys/time.h>
#include <irrlicht/vector3d.h>
#include <irrlicht/vector2d.h>
#include <ManageStrings.hpp>
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
	struct sockaddr_in client_sin;
	socklen_t client_sin_len = sizeof(client_sin);
	std::unique_ptr<Client> newClient = std::make_unique<Client>(id, accept(_hostFd, (struct sockaddr *)&client_sin, &client_sin_len), "Anonymous");

	dprintf(newClient->_fd, "%d\n", id);
	_clients.push_back(std::move(newClient));
	id += 1;
}

irr::f32 cutF(char *&str)
{
	return static_cast<irr::f32>(std::stof(strsep(&str, ":")));
}

int cutI(char *&str)
{
	return std::stoi(strsep(&str, ":"));
}

std::vector<std::vector<int>> Indie::Server::buildMap(const std::string &msg)
{
	std::vector<std::vector<int>> map;
	auto copy = (char *)msg.c_str();
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
			std::cout << "Client " << client->_id << " say " << tmp << std::endl;
			if (std::string(tmp) == "READY") {
				client->_state = PLAYING;
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
			auto enumPlayer = std::stoi(strsep(&tmp, ":"));
			auto enumMove = std::stoi(strsep(&tmp, ":"));
			auto enumId = std::stoi(strsep(&tmp, ":"));
			irr::core::vector2di position2d(std::stoi(strsep(&tmp, ":")), std::stoi(strsep(&tmp, ":")));// = {cutI(tmp), cutI(tmp)};
			irr::core::vector3df position3d(std::stof(strsep(&tmp, ":")), std::stof(strsep(&tmp, ":")), std::stof(strsep(&tmp, ":")));// = {cutF(tmp), cutF(tmp), cutF(tmp)};
			irr::f32 rotation = std::stof(strsep(&tmp, ":"));
			(void) rotation;
			(void) position3d;
			(void) enumId;
			(void) enumMove;
			(void) enumPlayer;
			if (_map[position2d.Y][position2d.X] == 0) {
				client->pos2d.Y = position2d.Y;
				client->pos2d.X = position2d.X;
				//_map[position2d.Y][position2d.X] == //ici mettre un nombre qui represente le joueur
				for (auto &i : _clients) {
					if (std::string(cmd).compare(0, 4, "1:4:") == 0)
						// Renvoyer les msg dans le menu d'attente
						dprintf(i->_fd, "1:4:%s: %s", client->_name.c_str(), &cmd[4]);
					else
						dprintf(i->_fd, cmd.c_str());
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
	struct timeval tv = {1, 0};

	if (select(maxFd() + 1, &_fdRead, nullptr, nullptr, &tv) == -1)
		throw std::runtime_error("Error while reading server socket");
	if (FD_ISSET(_hostFd, &_fdRead))
		addClient();
	for (unsigned i = 0 ; i < _clients.size() ; i++) {
		if (FD_ISSET(_clients[i]->_fd, &_fdRead))
			i = (readClient(_clients[i]) == 1 ? i - 1 : i);
	}
}

Indie::GameState Indie::Server::checkIfStartGame()
{
	unsigned spawnId = 0;

	if (_clients.empty())
		return WAITING;
	for (auto &client : _clients) {
		if (client->_state == WAITING)
			return WAITING;
	}
	for (auto &client : _clients) {
		std::cout << _mapMsg << std::endl;
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

void Indie::Server::start()
{
	// GERER LA DESTRUCTION DU SALON (tlm quitte / partie terminée etc..)
	while (1) {
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

bool Indie::operator!=(std::unique_ptr<Indie::Client> &lhs, std::unique_ptr<Indie::Client> &rhs)
{
	return !(lhs->_id == rhs->_id && lhs->_fd == rhs->_fd && lhs->_name == rhs->_name);
}

bool Indie::operator==(std::unique_ptr<Indie::Client> &lhs, std::unique_ptr<Indie::Client> &rhs)
{
	return (lhs->_id == rhs->_id && lhs->_fd == rhs->_fd && lhs->_name == rhs->_name);
}