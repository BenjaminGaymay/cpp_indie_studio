//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#pragma once

#include <vector>
#include <map>
#include "Window.hpp"
#include "SplashScreen.hpp"
#include "Menu.hpp"
#include "Graphism.hpp"
#include "Map.hpp"
#include "Server.hpp"
#include "Options.hpp"
#include "Events.hpp"
#include "Macro.hpp"

namespace Indie {
	class Player;

	class Core {
	public:
		Core();
		~Core();
		void run();
		void drawCaption();
		void processEvents();
		void cleanMap();
		void eraseTopandBot();
		void eraseLeftandRight();
		void editMap();
		int editMapEvents();
		void writeInFile(std::string file, std::vector<std::vector<int>> map);
		void createZeroMap(std::string name, size_t x, size_t y);
		int createRandMap(std::string name, size_t x, size_t y);
		int waitForId();
		void readServerInformations(std::vector<std::string>);
		void addPlayer(int, irr::core::vector3df &, const irr::f32 &);
		void removePlayer(int, irr::core::vector3df &, const irr::f32 &);
		void movePlayer(int, irr::core::vector3df &, const irr::f32 &);
		void checkAppContext();
		void handleMenu();
		void menuEvents();
		void sendMapToServer(const std::string &);


	private:
		int _lastFps;
		std::unique_ptr<Graphism> _graphism;
		Options m_opts;
		Window m_core;
		std::unique_ptr<Map> _mapper;
		std::unique_ptr<Map> _editing;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(int, irr::core::vector3df &, const irr::f32 &)> _playersFct;
		SplashScreen m_splash;
		Menu m_menu;
		AppState m_state;
		Events m_event;
		irr::video::SColor _color;
		GameState _state;
		int _playerId;
	};
}