/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** server
*/

#include "Server.hpp"

Indie::Server::Server()
{
	_socket = Socket(5567, INADDR_ANY, Indie::Socket::SERVER);
	_hostFd = _socket.getFd();
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
	for (auto &client : _clients) {
		// Stocker la pos de chaque client pour pouvoir l'envoyer
		std::cout << "Tlm sait que " << id << " a pop\n";
		std::cout << id << "connait la pos de" << client->_id << std::endl;
		dprintf(client->_fd, "0:0:%d:0:112:0\n", id); // PLAYER:APPEAR:x:y:z
		dprintf(newClient->_fd, "0:0:%d:0:112:0\n", client->_id); // mettre la pos du joueur
	}
	_clients.push_back(std::move(newClient));
	id += 1;
}

int Indie::Server::readClient(std::unique_ptr<Client> &client)
{
	char buffer[4096];
	char *tmp = NULL;
	int size;

	size = read(client->_fd, buffer, 4096);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp) {
			std::cout << "Client " << client->_id << " say " << tmp << std::endl;
			for (auto &i : _clients) {
				std::cout << "Client " << i->_id << " know " << tmp << std::endl;
				dprintf(i->_fd, tmp);
			}
			tmp = strtok(NULL, "\n");
		}
		return 0;
	}
	std::cout << "Client " << client->_id << " out" << std::endl;
	auto pos = std::find(_clients.begin(), _clients.end(), client);

	if (pos != _clients.end()) {
		pos->reset();
		_clients.erase(pos);
	}
	for (auto &client : _clients)
		dprintf(client->_fd, "0:1:%d:0:0:0\n", client->_id);
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

void Indie::Server::start()
{
	while (1) {
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

bool operator==(std::unique_ptr<Indie::Client> &lhs, std::unique_ptr<Indie::Client> &rhs)
{
	return (lhs->_id == rhs->_id && lhs->_fd == rhs->_fd && lhs->_name == rhs->_name);
}