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
			void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
			irr::scene::IAnimatedMeshSceneNode *createPalmier(irr::core::vector3df position, irr::core::vector3df rotation);
			irr::scene::IAnimatedMeshSceneNode *createSun(irr::core::vector3df position, irr::core::vector3df rotation);
			irr::scene::IAnimatedMeshSceneNode *createMoon(irr::core::vector3df position, irr::core::vector3df rotation);
			irr::scene::IAnimatedMeshSceneNode *createTexture(const irr::io::path &mesh, const irr::io::path &texture);
			void createIsland(irr::core::vector3df position, irr::core::vector3df rotation);
			void processEvents(const Events &);

		private:
			Window m_core;
			bool m_run;
	};
}