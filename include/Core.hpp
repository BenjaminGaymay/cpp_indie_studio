//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#pragma once

#include <vector>
#include <thread>
#include <map>
#include <ik_ISoundEngine.h>
#include "Window.hpp"
#include "SplashScreen.hpp"
#include "Menu.hpp"
#include "Graphism.hpp"
#include "Map.hpp"
#include "Server.hpp"
#include "Options.hpp"
#include "Events.hpp"
#include "Macro.hpp"
#include "Chat.hpp"
#include "Game.hpp"
#include <functional>

namespace Indie {
	class Player;
	class EventManager;

	enum editorState {
		BLOCK,
		INDESTRUCTIBLE_BLOCK,
		PERSO
	};

	class Core {
	public:
		Core();
		~Core();
		void init(Options &opt);
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
		void moveEvent(irr::core::vector3df &pos);
		void dropBombEvent(irr::core::vector3df &pos);
		void comPlayer(const ObjectsEvents &event, std::vector<std::string> &);
		void comBomb(const ObjectsEvents &event, std::vector<std::string> &);
		void comGameInfos(const ObjectsEvents &event, std::vector<std::string> &);
		void comMap(const ObjectsEvents &event, std::vector<std::string> &);
		void addPlayer(const int &id, const irr::core::vector2di &pos2d, const float &rotation, const float &speed, const std::size_t &power, const std::size_t &bombNumber, const bool &wallUp);
		void removePlayer(int, const ObjectsEvents &event);
		void movePlayer(int, const irr::core::vector2di &, const irr::core::vector3df &, const irr::f32 &);
		void takeBonus(const irr::core::vector2di &pos, const PowerUpType &bonus);
		void dropBomb(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos3d, const std::size_t &power);
		void createBlock(const Indie::PowerUpType &bonus, const irr::core::vector2di &pos);
		void destroyBlock(const irr::core::vector2di &target);
		void destroyBomb(const irr::core::vector2di &target);
		void serverMessage(const std::vector<std::string> &);
		void checkAppContext();
		void sendMapToServer(const std::string &);
		void changeMapWithEvent(std::size_t x, std::size_t y);
		void exitGame();
		void standPlayer(int id);
		void checkAppState();
		void infoReadyPlayerOne();
		void saveLocalGame(std::vector<std::string> &infos);
		void loadLocalGame(const std::string &fileName);

	public:
		int _lastFps;
		irrklang::ISoundEngine* _engine;
		std::unique_ptr<Game> _game;
		std::unique_ptr<EventManager> m_evtManager;
		std::unique_ptr<Graphism> _graphism;
		Options m_opts;
		Window m_core;
		std::unique_ptr<Map> _editing;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(const ObjectsEvents &event, std::vector<std::string> &)> _objectsFct;
		SplashScreen m_splash;
		Menu m_menu;
		AppState m_state;
		Events m_event;
		irr::video::SColor _color;
		GameState _state;
		Chat _chat;
		int _playerId;
		editorState _editState;
		std::pair<std::size_t, std::size_t> _counter;
		irr::core::vector3df pos;
		Clock playerClock;
		std::map<int, ObjectsEvents> _readyPlayers;
	};
}