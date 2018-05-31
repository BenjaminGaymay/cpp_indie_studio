/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventManager
*/

#pragma once

#include <iostream>
#include "Macro.hpp"

namespace Indie {
	class Core;

	class EventManager {
	public:
		EventManager();
		EventManager(Core *);
		~EventManager();

		void manage();
		void init(Core *);

	private:
		Core *m_core;
	};
}