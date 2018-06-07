//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// EventManager
//

#pragma once

#include <iostream>
#include <ik_ISoundEngine.h>
#include <irrlicht.h>
#include "Macro.hpp"

namespace Indie {
	class Core;

	class EventManager {
	public:
		EventManager();
		EventManager(Core *);
		~EventManager();

		void manage(irrklang::ISoundEngine* engine);
		void init(Core *);
		void updateIpInput(irr::s32);
		void checkMapNameValid();
	private:
		Core *m_core;
	};
}