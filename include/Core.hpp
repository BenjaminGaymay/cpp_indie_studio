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
		int waitForId();
		void readServerInformations(std::vector<std::string>);
		void addPlayer(int, irr::core::vector3df &, const irr::f32 &);
		void removePlayer(int, irr::core::vector3df &, const irr::f32 &);
		void movePlayer(int, irr::core::vector3df &, const irr::f32 &);
		void handleMenu();

	private:
		int _lastFps;
		std::unique_ptr<Graphism> _graphism;
		Window m_core;
		std::unique_ptr<Map> _mapper;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(int, irr::core::vector3df &, const irr::f32 &)> _playersFct;
		SplashScreen m_splash;
		Menu m_menu;
		State m_state;
		Events m_event;
		irr::video::SColor _color;
	};
}