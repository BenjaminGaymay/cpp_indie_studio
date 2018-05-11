/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Events
*/

#pragma once

#include <irrlicht/irrlicht.h>

namespace Indie {
	struct SMouseState {
		irr::core::position2di Position;
		bool LeftButtonDown;
		SMouseState();
	};

	class Events : public irr::IEventReceiver {
		public:
			Events();
			virtual bool OnEvent(const irr::SEvent &);
			virtual bool isKeyDown(irr::EKEY_CODE) const;

		public:
			SMouseState MouseState;
		private:
			bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
}