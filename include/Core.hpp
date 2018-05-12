/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include <map>
#include "Window.hpp"
#include "Map.hpp"

namespace Indie {
	class Core {
	private:
		void generateTextureMap();
	private:
		/* FIRST object, SECOND texture */
		using textureElem = std::pair<irr::io::path, irr::io::path>;
		std::map<int, textureElem> _texturesMap;
		Window m_core;
		bool m_run;
		public:
			Core();
			~Core();
			void run();
			void drawCaption(int &);
			void buildDecor();
			void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
			irr::scene::IAnimatedMeshSceneNode *createTexture(const textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale);
			void moveTexture(irr::scene::IAnimatedMeshSceneNode *node, const irr::core::vector3df &position);
			irr::scene::IAnimatedMeshSceneNode *createIsland(irr::core::vector3df position, irr::core::vector3df rotation);
			void processEvents(const Events &);
	};
}