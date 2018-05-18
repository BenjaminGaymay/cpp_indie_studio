/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Events
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "Menu.hpp"
#include "Options.hpp"

namespace Indie {

	struct SMouseState {
		irr::core::position2di Position;
		bool LeftButtonDown;
		SMouseState();
	};

	struct AppContext {
		irr::IrrlichtDevice *device;
		Menu *menu;
		Options *options;
	};

	class Events : public irr::IEventReceiver {
		public:
			Events();
			virtual bool OnEvent(const irr::SEvent &);
			virtual bool isKeyDown(irr::EKEY_CODE) const;
			void load(AppContext &);

		public:
			SMouseState MouseState;
			AppContext Context;
		private:
			bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}