//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Server
//

#pragma once

#include <memory>
#include <algorithm>
#include <vector2d.h>
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
			Client(int id, int fd, const std::string &name) : _id(id), _fd(fd), _name(name), _state(WAITING), _alive(true) {}
			int _id;
			int _fd;
			std::string _name;
			GameState _state;
			irr::core::vector2di pos2d;
			bool _alive;
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
			bool hitPlayer(const irr::core::vector2di &target, const int &id);
			void manageBomb();
			void replaceByBonus(const irr::core::vector2di &pos);
			bool wallMove(std::unique_ptr<Client> &client, irr::core::vector3df &pos3d, irr::core::vector2di &pos2d, irr::f32 &rotation);
			bool validMove(const int &block);
			void comPlayer(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			void comBomb(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			void comGameInfos(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			void comMap(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &);
			std::vector<std::vector<int>> buildMap(const std::string &msg);
			int getBlock(irr::core::vector2di &pos) const { return _map[pos.Y][pos.X]; }
			void setBlock(irr::core::vector2di &pos, int value) { _map[pos.Y][pos.X] = value; }
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
			std::string _lastCmd;
			std::vector<void (Indie::Server::*)(const ObjectsEvents &event, std::vector<std::string> &, std::unique_ptr<Client> &)> _objectsFct;
	};

}

