/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include <vector>
#include <map>
#include "Socket.hpp"
#include "Window.hpp"
#include "SplashScreen.hpp"
#include "Menu.hpp"
#include "Graphism.hpp"
#include "Map.hpp"

namespace Indie {
	class Player;
	class ObjectPlayer;

	enum State {
		MENU,
		MAPPING,
		GAME
	};

	class Core {
	public:
		Core();
		~Core();
		void run();
		void drawCaption();
		void processEvents();
		int waitForId(Indie::Graphism &graphism);
		void readServerInformations(std::vector<std::string>, Indie::Graphism &graphism);
		void addPlayer(Indie::Graphism &core, int, irr::core::vector3df &);
		void removePlayer(Indie::Graphism &core, int, irr::core::vector3df &);
		void movePlayer(Indie::Graphism &core, int, irr::core::vector3df &);
		void handleMenu();
		void create_rand_map(std::string name, size_t x, size_t y);
		void createZeroMap(std::string name, size_t x, size_t y);
		void write_in_file(std::string file, std::vector<std::vector<int>> map);
		void editMap(Graphism graphism);
		int EditMapEvents();
		void cleanMap();

	private:
		int _lastFps;
		Window m_core;
		std::unique_ptr<Map> _mapper;
		std::unique_ptr<Map> _editing;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(Indie::Graphism &, int, irr::core::vector3df &)> _playersFct;
		SplashScreen m_splash;
		Menu m_menu;
		State m_state;
		Events m_event;
		irr::video::SColor _color;
	};
}