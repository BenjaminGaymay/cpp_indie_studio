/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Menu
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <iostream>
#include <vector>
#include "Options.hpp"

namespace Indie {

	enum {
		GUI_ID_QUIT_BUTTON = 101,
		GUI_ID_PLAY_BUTTON,
		GUI_ID_OPTIONS_BUTTON,
		GUI_ID_SERVER_BUTTON,
		GUI_ID_MAP_BUTTON,
		GUI_ID_PLAY_MENU_ELEMENT,
		GUI_ID_OPTION_MENU_ELEMENT,
		GUI_ID_MAP_EDIT_MENU_ELEMENT,
		GUI_ID_MAIN_MENU_ELEMENT,
		GUI_ID_ROOM_MENU_ELEMENT,
		GUI_ID_ROOM_BACK_BUTTON,
		GUI_ID_OPTION_BACK_BUTTON,
		GUI_ID_PLAY_BACK_BUTTON,
		GUI_ID_MAP_BACK_BUTTON,
		GUI_ID_FULLSCREEN,
		GUI_ID_PLAY_SERVER,
		GUI_ID_PLAY_CLIENT,
		GUI_ID_READY,
		GUI_ID_MAP_EDITOR_BUTTON,
		GUI_ID_MAP_RANDOM_BUTTON
	};


	enum AppState {
		MENU,
		QUIT,
		OPTION,
		GEN_MAP,
		MAPPING,
		LAUNCH_SERVER,
		CONNECT,
		READY,
		PLAY,
		NONE
	};

	struct SpriteMenu {
	public:
		SpriteMenu() {};
		~SpriteMenu() {};
		std::vector<irr::core::recti> m_images;
		irr::core::recti m_zone;
		AppState  m_return;
	};

	class Menu {
	public:
		Menu();
		~Menu();
		void loadMenu(irr::IrrlichtDevice *, const Options &);
		AppState display();
		void initSpriteMenu(std::vector<SpriteMenu> &);

		void loadMainMenu();
		void loadOptionsMenu();
		void loadMapMenu();
		void loadPlayMenu();
		void loadRoomMenu();

		void setSkinTransparency(irr::s32 , irr::gui::IGUISkin *);

	public:
		irr::gui::IGUIElement *m_root;
		irr::gui::IGUIElement *m_main;
		irr::gui::IGUIElement *m_option;
		irr::gui::IGUIElement *m_play;
		irr::gui::IGUIElement *m_mapEdit;
		irr::gui::IGUIElement *m_room;

		irr::gui::IGUIElement *m_server;

	private:
		irr::gui::IGUIFont *m_font;
		irr::scene::ISceneManager *m_sceneManager;
		irr::video::IVideoDriver *m_driver;
		irr::gui::IGUIEnvironment *m_gui;
		irr::video::ITexture* m_images;
		std::vector<irr::gui::IGUIButton *> m_btns;
		Options m_opt;
		std::size_t m_height;
		std::size_t m_width;
	};
}