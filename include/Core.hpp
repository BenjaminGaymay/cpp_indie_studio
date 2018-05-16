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
		GAME
	};

	class Core {
	public:
		Core();
		~Core();
		void run();
		void drawCaption(int &);
		void processEvents();
		int waitForId(Indie::Graphism &graphism);
		void readServerInformations(std::vector<std::string> &, Indie::Graphism &graphism);
		void addPlayer(Indie::Graphism &core, int, irr::core::vector3df &);
		void removePlayer(Indie::Graphism &core, int, irr::core::vector3df &);
		void movePlayer(Indie::Graphism &core, int, irr::core::vector3df &);
		void handleMenu();

	private:
		Window m_core;
		std::unique_ptr<Map> _mapper;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(Indie::Graphism &, int, irr::core::vector3df &)> _playersFct;
		SplashScreen m_splash;
		Menu m_menu;
		State m_state;
		Events m_event;
	};
}