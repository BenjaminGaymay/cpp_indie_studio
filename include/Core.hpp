/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include "Window.hpp"

namespace Indie {
	class Core {
		public:
			Core();
			~Core();
			void run();
		private:
			Window m_core;
	};
}