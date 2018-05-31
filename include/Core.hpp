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
	class EventManager;

	enum editorState {
		BLOCK,
		PERSO
	};

	struct s_tchat {
		bool _getch;
		std::vector<std::string> _messages;
		irr::gui::IGUIEditBox *_textBox;
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
		void moveEvent(irr::core::vector3df &pos, Clock &);
		void dropBombEvent(irr::core::vector3df &pos, Clock &);
		void comPlayer(int, std::vector<std::string> &);
		void comBomb(int, std::vector<std::string> &);
		void addPlayer(int, const irr::core::vector2di &);
		void removePlayer(int);
		void movePlayer(int, const irr::core::vector2di &, const irr::core::vector3df &, const irr::f32 &);
		void dropBomb(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos3d, const std::size_t &power);
		void createBlock(const Indie::PowerUpType &bonus, const irr::core::vector2di &pos);
		bool findAndDestroyEntity(const irr::core::vector2di &target);
		void takeBonus(const irr::core::vector2di &pos, const PowerUpType &bonus);
		void destroyBlock(const irr::core::vector2di &target);
		void destroyBomb(const irr::core::vector2di &target);
		void comGameInfos(int, std::vector<std::string> &);
		void comMap(int, std::vector<std::string> &);
		void serverMessage(const std::vector<std::string> &);
		void checkAppContext();
		void handleMenu();
		void menuEvents();
		void sendMapToServer(const std::string &);
		void manageTchat();
		void printTchat() const;
		void changeMapWithEvent(std::size_t x, std::size_t y);
		void exitGame();

	// public:
	// 	Events getEvent() const {
	// 		return m_event;
	// 	}

	// 	void setEvent(const Events &evt) {
	// 		m_event = evt;
	// 	}

	// 	GameState getGameState() const {
	// 		return _state;
	// 	}

	// 	void setGameState(const GameState &state) {
	// 		_state = state;
	// 	}

	// 	AppState getAppState() const {
	// 		return m_state;
	// 	}

	// 	void setAppState(const AppState &state) {
	// 		m_state = state;
	// 	}

	// 	SplashScreen getSplashScreen() const {
	// 		return m_splash;
	// 	}

	// 	bool isRunning() const {
	// 		return m_run;
	// 	}

	// 	void setRun(const bool &run) {
	// 		m_run = run;
	// 	}

	// 	Options getOptions() const {
	// 		return m_opts;
	// 	}

	// 	void setOptions(const Options &opt) {
	// 		m_opts = opt;
	// 	}

	// 	Window getWindow() const {
	// 		return m_core;
	// 	}

	// 	// Map getMap() const {
	// 	// 	return *_mapper.get();
	// 	// }

	// 	// Map getEditing() const {
	// 	// 	return *_editing.get();
	// 	// }

	// 	// std::vector<std::unique_ptr<Player>> getPlayers() const {
	// 	// 	return _playerObjects;
	// 	// }

	// 	s_tchat getChat() const {
	// 		return _tchat;
	// 	}

	// 	int getPlayerId() const {
	// 		return _playerId;
	// 	}

	// 	editorState getEditState() const {
	// 		return _editState;
	// 	}

	// 	void setEditState(const editorState &state) {
	// 		_editState = state;
	// 	}

	// 	Menu getMenu() const {
	// 		return m_menu;
	// 	}

	// private:
		int _lastFps;
		std::unique_ptr<EventManager> m_evtManager;
		std::unique_ptr<Graphism> _graphism;
		Options m_opts;
		Window m_core;
		std::unique_ptr<Map> _mapper;
		std::unique_ptr<Map> _editing;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(int, std::vector<std::string> &)> _objectsFct;
		SplashScreen m_splash;
		Menu m_menu;
		AppState m_state;
		Events m_event;
		irr::video::SColor _color;
		GameState _state;
		s_tchat _tchat;
		int _playerId;
		editorState _editState;
		std::pair<std::size_t, std::size_t> _counter;
		bool m_bappe;
	};
}