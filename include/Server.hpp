/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Server
*/

#pragma once

#include "Socket.hpp"
#include <memory>
#include <algorithm>

namespace Indie {
	class Client {
		public:
			Client(int id, int fd, const std::string &name) : _id(id), _fd(fd), _name(name) {}
			int _id;
			int _fd;
			std::string _name;
	};

	bool operator==(std::unique_ptr<Client> &, std::unique_ptr<Client> &);

	class Server {
		public:
			Server();
			void start();
			void setClientsFds();
			void readOnFds();
			int maxFd() const;
			void addClient();
			int readClient(std::unique_ptr<Client> &);
			static void runServer();
		private:
			fd_set _fdRead;

			Socket _socket;
			int _hostFd;
			std::vector<std::unique_ptr<Client>> _clients;
	};

}

