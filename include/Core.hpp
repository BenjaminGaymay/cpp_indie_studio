/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include "Irrlicht.hpp"

namespace Indie {
	class Core {
		public:
			Core();
			~Core();
			void run();
		private:
			Irrlicht m_core;
	};
}