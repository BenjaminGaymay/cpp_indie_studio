/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** SplashScreen
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "Clock.hpp"

namespace Indie {
	class SplashScreen {
	public:
		SplashScreen();
		~SplashScreen();
		void display(irr::IrrlichtDevice *);
		bool fadeIn();
		bool fadeOut();

	private:
		irr::gui::IGUIEnvironment *m_gui;
		irr::gui::IGUIInOutFader *m_fader;
		irr::video::IVideoDriver *m_driver;
		irr::video::ITexture *m_texture;
		Clock m_clock;
	};
}