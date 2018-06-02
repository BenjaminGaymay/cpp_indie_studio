//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Events
//

#pragma once

#include <unordered_map>
#include <ik_ISoundEngine.h>
#include "Menu.hpp"
#include "Options.hpp"
#include "Macro.hpp"

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
		AppState *state;
	};

	class Events : public irr::IEventReceiver {
		public:
			Events();
			virtual bool OnEvent(const irr::SEvent &);
			virtual bool isKeyDown(irr::EKEY_CODE) const;
			bool isButtonClicked(IdGui);
			void setKeyUp(irr::EKEY_CODE key) { KeyIsDown[key] = false; }
		public:
			SMouseState MouseState;
		private:
			bool ButtonClicked[BTN_COUNT];
			bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}