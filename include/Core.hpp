/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include <vector>
#include <map>
#include "Window.hpp"

namespace Indie {
	class Core {
	public:
		Core();
		~Core();
		void run();
		void drawCaption(int &);
		void processEvents(const Events &);
	private:
		Window m_core;
		bool m_run;
	};
}