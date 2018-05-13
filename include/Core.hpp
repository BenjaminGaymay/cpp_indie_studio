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
	public:
		using textureElem = std::pair<irr::io::path, irr::io::path>;
		Core();

		~Core();
		void run();
		void drawCaption(int &);
		void buildDecor();
		void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
		 irr::scene::IAnimatedMeshSceneNode *createTexture(textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale);
		irr::scene::IAnimatedMeshSceneNode *createIsland(irr::core::vector3df position, irr::core::vector3df rotation);
		void processEvents(const Events &);
	private:
		void generateTextureMap();
		/* FIRST object, SECOND texture */
		std::map<int, textureElem> _texturesMap;
		Window m_core;
		bool m_run;
	};
}