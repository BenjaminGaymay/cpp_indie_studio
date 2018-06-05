//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Socket
//

#include "Socket.hpp"

Indie::Socket::Socket(const int port, const std::string &addr, TypeSocket type) :
		_port(port), _addr(addr), _inetAddr(inet_addr(addr.c_str())), _type(type)
{
	struct protoent *pe;
	int options = 1;

	pe = getprotobyname("TCP");
	if (! pe)
		throw std::runtime_error("Error: getprotobyname failed");
	_fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(int)) < 0)
		throw std::runtime_error("Error: setsockopt failed");
	if (_fd == -1)
		throw std::runtime_error("Error: socket failed");
	_sIn.sin_family = AF_INET;
	_sIn.sin_port = htons(port);
	_sIn.sin_addr.s_addr = _inetAddr;

	if (type == SERVER) {
		if (bind(_fd, (const struct sockaddr *)&_sIn, sizeof(_sIn)) == -1) {
			close(_fd);
			throw std::runtime_error("Error: bind failed");
		}
		if (listen(_fd, 42) == -1)
			throw std::runtime_error("Error: listen failed");
	} else if (connect(_fd, (struct sockaddr *)&_sIn, sizeof(_sIn)) == -1) {
		close(_fd);
		throw std::runtime_error("Error: connect failed");
	}
}

Indie::Socket::Socket(const int port, const in_addr_t &addr, TypeSocket type) :
		_port(port), _addr("INADDR_ANY"), _inetAddr(addr), _type(type)
{
	struct protoent *pe;
	int options = 1;

	pe = getprotobyname("TCP");
	if (! pe)
		throw std::runtime_error("Error: getprotobyname failed");
	_fd = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(int)) < 0)
		throw std::runtime_error("Error: setsockopt failed");
	if (_fd == -1)
		throw std::runtime_error("Error: socket failed");
	_sIn.sin_family = AF_INET;
	_sIn.sin_port = htons(port);
	_sIn.sin_addr.s_addr = _inetAddr;

	if (type == SERVER) {
		if (bind(_fd, (const struct sockaddr *)&_sIn, sizeof(_sIn)) == -1) {
			close(_fd);
			throw std::runtime_error("Error: bind failed");
		}
		if (listen(_fd, 42) == -1)
			throw std::runtime_error("Error: listen failed");
	} else if (connect(_fd, (struct sockaddr *)&_sIn, sizeof(_sIn)) == -1) {
		close(_fd);
		throw std::runtime_error("Error: connect failed");
	}
}

void Indie::Socket::sendInfos(Indie::ObjectsType type, Indie::ObjectsEvents event, const std::string &infos)
{
	dprintf(_fd, "%d:%d:%s\n", type, event, infos.c_str());
}

bool Indie::Socket::isSocketWritten()
{
	struct timeval tv = {0, 50};

	FD_ZERO(&_fdRead);
	FD_SET(_fd, &_fdRead);
	if (select(_fd + 1, &_fdRead, nullptr, nullptr, &tv) == -1)
		throw std::runtime_error("Error while reading socket");
	return FD_ISSET(_fd, &_fdRead);
}

std::vector<std::string> Indie::Socket::readSocket()
{
	static char buffer[8192];
	char *tmp = nullptr;
	std::vector<std::string> socketContents;
	ssize_t size;

	if (!isSocketWritten())
		return socketContents;
	size = read(_fd, buffer, 8192);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp) {
			socketContents.emplace_back(tmp);
			tmp = strtok(nullptr, "\n");
		}
		return socketContents;
	}
	throw std::runtime_error("Error: server is down");
}