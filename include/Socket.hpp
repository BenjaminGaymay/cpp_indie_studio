//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Socket
//

#pragma once

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <vector>

namespace Indie {
	enum PowerUpType {
		FIRST_UP = 3,
		SPEED_UP = 4,
		BOMB_UP = 5,
		FIRE_UP = 6,
		WALLPASS_UP = 7,
		LAST_UP = 8//don't use it
	};
	enum ObjectsType {
		PLAYER,
		GAMEINFOS,
		MAP,
		BOMB
	};

	enum ObjectsEvents {
		APPEAR,
		DEAD,
		MOVE,
		START,
		MESSAGE,
		CREATEBOMB,
		DESTROYBOMB,
		DESTROYBLOCK,
		CREATEBLOCK,
		TAKEBONUS,
		EV_READY,
		EV_UNREADY,
		SUICIDE,
		STAND,
		LEAVE,
		INFO,
		EXIT,
		NICK
	};

	class Socket {
		public:
			enum TypeSocket {
				SERVER,
				CLIENT
			};
			Socket() {}
			~Socket() {}
			Socket(const int, const std::string &, TypeSocket);
			Socket(const int, const in_addr_t &, TypeSocket);
			int getPort() const { return _port; }
			std::string getAddr() const { return _addr; }
			in_addr_t getInetAddr() const { return _inetAddr; }
			TypeSocket getType() const { return _type; }
			int getFd() const { return _fd; }
			void sendInfos(ObjectsType, ObjectsEvents, const std::string &);
			bool isSocketWritten();
			std::vector<std::string> readSocket();
			void closeSocket() { close(_fd); }
		private:
			int _port;
			std::string _addr;
			in_addr_t _inetAddr;
			TypeSocket _type;

			int _fd;
			struct sockaddr_in _sIn;
			fd_set _fdRead;
	};
}