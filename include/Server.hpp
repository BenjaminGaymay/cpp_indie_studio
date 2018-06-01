//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Server
//

#pragma once

#include <memory>
#include <algorithm>
#include <irrlicht/vector2d.h>
#include "Socket.hpp"
#include "Bomb.hpp"

namespace Indie {
	enum GameState {
		NOTCONNECTED,
		WAITING,
		PLAYING
	};

	class Client {
		public:
			Client(int id, int fd, const std::string &name) : _id(id), _fd(fd), _name(name), _state(WAITING) {}
			int _id;
			int _fd;
			std::string _name;
			GameState _state;
			irr::core::vector2di pos2d;
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
			void destroyEntities(std::unique_ptr<Indie::Bomb> &bomb);
			bool hitPlayer(const irr::core::vector2di &target);
			void manageBomb();
			void replaceByBonus(const irr::core::vector2di &pos);
			bool wallMove(std::unique_ptr<Client> &client, irr::core::vector3df &pos3d, irr::core::vector2di &pos2d, irr::f32 &rotation);
			bool validMove(const int &block);
			std::vector<std::vector<int>> buildMap(const std::string &msg);
		private:
			fd_set _fdRead;
			Socket _socket;
			int _hostFd;
			GameState _state;
			std::vector<std::unique_ptr<Client>> _clients;
			std::vector<std::unique_ptr<Indie::Bomb>> _bombs;
			std::vector<std::vector<int>> _map;
			std::vector<std::vector<int>> _spawn;
			std::string _mapMsg;
	};

}

