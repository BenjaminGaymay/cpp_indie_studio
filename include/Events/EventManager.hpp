/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventManager
*/

#pragma once
#include "Core.hpp"

namespace Indie {

	class EventManager {
	public:
		EventManager();
		EventManager(Core &);
		~EventManager();

		void init(Core &);

	private:
		Core *m_core;
	};
}