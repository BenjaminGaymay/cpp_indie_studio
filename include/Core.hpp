/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include "Window.hpp"
#include "Map.hpp"

namespace Indie {
	class Core {
		public:
			Core();
			~Core();
			void run();
			void drawCaption(int &);
			void buildDecor();
			void createPalmier(irr::core::vector3df position);
			void processEvents(const Events &);

		private:
			Window m_core;
			bool m_run;
	};
}