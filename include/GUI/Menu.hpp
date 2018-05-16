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
#include <array>
#include "Events.hpp"

namespace Indie {

	enum MenuState {
		PLAY,
		QUIT,
		OPTION,
		GEN_MAP,
		LAUNCH_SERVER,
		NONE
	};

	struct SpriteMenu {
	public:
		SpriteMenu() {};
		~SpriteMenu() {};
		std::vector<irr::core::recti> m_images;
		irr::core::recti m_zone;
		MenuState  m_return;
	};

	class Menu {
	public:
		Menu();
		~Menu();
		void loadMenu(irr::IrrlichtDevice *);
		MenuState display(const Events &);
		void initSpriteMenu(std::array<SpriteMenu, 2> &);

	private:
		irr::scene::ISceneManager *m_sceneManager;
		irr::video::IVideoDriver *m_driver;
		irr::gui::IGUIEnvironment *m_gui;
		irr::video::ITexture* m_images;
	};
}