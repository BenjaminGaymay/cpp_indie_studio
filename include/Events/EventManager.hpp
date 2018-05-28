/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventManager
*/

#pragma once

class Core;

namespace Indie {
	class EventManager {
	public:
		EventManager();
		EventManager(Core &);
		~EventManager();

	private:
		Core &m_core;
	};
}