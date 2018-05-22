/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** server
*/

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

void Indie::Server::is_valid_move(std::unique_ptr<Indie::Client> &client, Indie::Response &response)
{
	if (_map[response._data._pos3d.X][response._data._pos3d.Y] != 0) // tmp condition, player must be move into flame, take bonus...
		response._data._pos3d = client->_data._pos3d; //cancel move
}

int Indie::Server::readClient(std::unique_ptr<Client> &client)
{
	char buffer[4096];
	char *tmp = nullptr;
	ssize_t size;

	size = read(client->_fd, buffer, 4096);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp) {
			std::cout << "Client " << client->_id << " say " << tmp << std::endl;
			if (std::string(tmp) == "READY")
				client->_state = PLAYING;
			if (_state == WAITING)
				return 0;

			Response response(tmp);

			//we must check if this command is a move
			switch (response._data.type) {
				case(messageType::PLAYER_MOVE) : is_valid_move(client, response); break;
				case(messageType::PLAYER_LEAVE) : break;
				case(messageType::BOMB_DROP) : break;
				default: break;
			}
			client->_data = response._data;
			std::string relay = response.unserialize();
			for (auto &i : _clients)
				dprintf(i->_fd, relay.c_str());
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
	// je dit à tous le monde que je suis mort
	for (auto &client : _clients)
		dprintf(client->_fd, "0:1:%d:0:0:0:0\n", client->_id);
	return 1;
}

void Indie::Server::readOnFds()
{
	struct timeval tv = {1, 0};

	if (select(maxFd() + 1, &_fdRead, NULL, NULL, &tv) == -1)
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
	if (_clients.empty())
		return WAITING;
	for (auto &client : _clients) {
		if (client->_state == WAITING)
			return WAITING;
	}
	for (auto &client : _clients)
		dprintf(client->_fd, "1:3\n"); // CODE POUR GAME START

	// on envoie à tous le monde la pos de tout le monde au départ du jeu
	// On donne la pos de chaque joueur
	for (auto &client : _clients) {
		// Stocker la pos de chaque client pour pouvoir l'envoyer
		for (auto &pop : _clients) {
			if (client != pop)
				dprintf(client->_fd, "0:0:%d:%f:%f:%f:%f\n", pop->_id, pop->_data._pos3d.X, pop->_data._pos3d.Y, pop->_data._pos3d.Z, pop->_data._rotation); // PLAYER:APPEAR:x:y:z:rotation
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