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
		using textureElem = std::pair<irr::io::path, irr::io::path>;
		Core();

		~Core();
		void run();
		void drawCaption(int &);
		void buildDecor();
		void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
		void createArena();
		irr::f32 resizeNode(irr::scene::IAnimatedMeshSceneNode *node, const float &size);
		 irr::scene::IAnimatedMeshSceneNode *createTexture(const textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale, bool collision);
		irr::scene::IAnimatedMeshSceneNode *createIsland(irr::core::vector3df position, irr::core::vector3df rotation);
		void setCollision(irr::scene::ISceneNode *wall, irr::scene::ISceneNode *target);
		void processEvents(const Events &);
		const textureElem *getTexture(const int &nb);
	private:
		void generateTextureMap();
		/* FIRST object, SECOND texture */
		std::map<int, textureElem> _texturesMap;
		std::vector<irr::scene::IAnimatedMeshSceneNode *> _nodesList;
		Window m_core;
		bool m_run;
	};
}