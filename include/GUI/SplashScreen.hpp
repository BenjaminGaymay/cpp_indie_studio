//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// SplashScreen
//

#pragma once

#include "Clock.hpp"
#include "Events.hpp"

namespace Indie {
	class SplashScreen {
	public:
		SplashScreen();
		~SplashScreen();
		void display(irr::IrrlichtDevice *, Events &);
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