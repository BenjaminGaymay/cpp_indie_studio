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

Indie::Server::Server() : _socket(
		Socket(5567, INADDR_ANY, Indie::Socket::SERVER)),
						  _hostFd(_socket.getFd()), _state(WAITING)
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
	std::unique_ptr<Client> newClient = std::make_unique<Client>(id, accept(_hostFd, (struct sockaddr *) &client_sin, &client_sin_len), "Anonymous");

	dprintf(newClient->_fd, "%d\n", id);
	_clients.push_back(std::move(newClient));
	id += 1;
}

std::vector<std::vector<int>> Indie::Server::buildMap(const std::string &msg)
{
	std::vector<std::vector<int>> map;
	auto copy = (char *) msg.c_str();
	char *line = strtok(copy, ":");

	while (line != nullptr) {
		std::vector<int> tmp;
		std::vector<std::string> oneLine;
		std::string str(line);

		oneLine = ManageStrings::splitString(str, ' ');
		for (auto &nb : oneLine)
			tmp.push_back(std::stoi(nb));
		map.push_back(tmp);
		line = strtok(nullptr, ":");
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
			std::cout << "Client " << client->_id << " say " << tmp
					  << std::endl;
			if (std::string(tmp) == "READY") {
				client->_state = PLAYING;
				break;
			}
			// >> reception map
			if (std::string(tmp).compare(0, 4, "2:0:") == 0) {
				_mapMsg = std::string(tmp);
				_map.clear();
				_map = buildMap(&tmp[4]);
			}
			// <<
			if (_state == WAITING)
				return 0;
			std::string cmd = tmp;
			auto enumType = std::stoi(strsep(&tmp, ":")); //PLAYER
			auto enumEvent = std::stoi(strsep(&tmp, ":")); //MOVE
			if (enumType == BOMB && enumEvent == CREATEBOMB) {
				auto enumId = std::stoi(strsep(&tmp, ":"));
				(void) enumId;
				irr::core::vector2di position2d(std::stoi(strsep(&tmp, ":")), std::stoi(strsep(&tmp, ":")));
				irr::core::vector3df position3d(std::stof(strsep(&tmp, ":")), std::stof(strsep(&tmp, ":")), std::stof(strsep(&tmp, ":")));
				std::size_t power = std::stoul(strsep(&tmp, ":"));
				(void) position3d;
				if (_map[position2d.Y][position2d.X] == 0) {
					std::unique_ptr<Indie::Bomb> mdr = std::make_unique<Indie::Bomb>(5, power, position2d);
					_bombs.push_back(std::move(mdr));
					_map[position2d.Y][position2d.X] = 3;
					for (auto &i : _clients)
						dprintf(i->_fd, cmd.c_str());
				}
			} else if (enumType == PLAYER && enumEvent == MOVE) {
				auto enumId = std::stoi(strsep(&tmp, ":"));
				irr::core::vector2di position2d(std::stoi(strsep(&tmp, ":")), std::stoi(strsep(&tmp, ":")));
				irr::core::vector3df position3d(std::stof(strsep(&tmp, ":")), std::stof(strsep(&tmp, ":")), std::stof(strsep(&tmp, ":")));
				irr::f32 rotation = std::stof(strsep(&tmp, ":"));
				(void) rotation;
				(void) position3d;
				(void) enumId;
				if ((_map[client->pos2d.Y][client->pos2d.X] == 1 && _map[position2d.Y][position2d.X] == 3) /* sinon on reste bloqué contre le mur*/
					|| (_map[client->pos2d.Y][client->pos2d.X] == 3) /* sinon on reste bloqué dans la bomb qu'on vient de drop*/
					|| (_map[position2d.Y][position2d.X] == 0)) /*normal*/{
					client->pos2d.Y = position2d.Y;
					client->pos2d.X = position2d.X;
					//_map[position2d.Y][position2d.X] == //ici mettre un nombre qui represente le joueur
					for (auto &i : _clients)
							dprintf(i->_fd, cmd.c_str());
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
		dprintf(aClient->_fd, "0:1:%d:0:0:0:0:0:0\n", aClient->_id);
	return 1;
}

void Indie::Server::readOnFds()
{
	struct timeval tv = {1, 0};

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
	}

	// On donne la pos de chaque joueur
	for (auto &client : _clients) {
		// Stocker la pos de chaque client pour pouvoir l'envoyer
		for (auto &pop : _clients) {
			if (client != pop)
				dprintf(client->_fd, "0:0:%d:0:112:0:0\n",
						pop->_id); // PLAYER:APPEAR:x:y:z:rotation
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