/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Server
*/

#pragma once

#include "Socket.hpp"
#include "ManageStrings.hpp"
#include <memory>
#include <algorithm>
#include <irrlicht/irrTypes.h>
#include <irrlicht/vector2d.h>
#include <irrlicht/vector3d.h>
#include <cstring>
#include <sstream>
#include "Response.hpp"

namespace Indie {
	enum GameState {
		NOTCONNECTED,
		WAITING,
		PLAYING
	};

	class Client {
		public:
			Client(int id, int fd, const std::string &name) : _id(id), _fd(fd), _name(name), _state(WAITING) {}
			~Client() = default;
			int _id;
			int _fd;
			std::string _name;
			GameState _state;
			Data _data;
	};

	bool operator==(std::unique_ptr<Client> &, std::unique_ptr<Client> &);
	bool operator!=(std::unique_ptr<Client> &, std::unique_ptr<Client> &);

	class Server {
		public:
			Server();
			void start();
			void setClientsFds();
			void readOnFds();
			int maxFd() const;
			void addClient();
			int readClient(std::unique_ptr<Client> &);
			GameState checkIfStartGame();
			static void runServer();
			/* fonction for game */
			void is_valid_move(std::unique_ptr<Indie::Client> &client, Indie::Response &response);
		private:
			fd_set _fdRead;

			Socket _socket;
			int _hostFd;
			GameState _state;
			std::vector<std::unique_ptr<Client>> _clients;
			std::vector<std::vector<int>> _map; //must be fill by host
	};

}

