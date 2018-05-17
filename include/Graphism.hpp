/*
** EPITECH PROJECT, 2018
** student
** File description:
** 16/05/18
*/

#ifndef BOMBERMAN_GRAPHISM_HPP
#define BOMBERMAN_GRAPHISM_HPP

#include <vector>
#include <map>
#include "Window.hpp"

namespace Indie {
	class Graphism {
	public:
		using textureElem = std::pair<irr::io::path, irr::io::path>;
		explicit Graphism(Window *m_core);
		~Graphism();
		void buildDecor();
		void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
		void addCollision(irr::scene::ISceneNode *object);
		irr::f32 resizeNode(irr::scene::ISceneNode *node, const float &size);
		irr::scene::ISceneNode *createTexture(const textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale, bool collision);
		irr::scene::ISceneNode *createIsland(irr::core::vector3df position, irr::core::vector3df rotation);
		void setCollision(irr::scene::ISceneNode *wall, irr::scene::ISceneNode *target);
		const textureElem *getTexture(const int &nb);
	private:
		void generateTextureMap();
		/* FIRST object, SECOND texture */
		std::map<int, textureElem> _texturesMap;
		std::vector<irr::scene::ISceneNode *> _nodesList;
		Window *m_core;
	};
}

#endif //BOMBERMAN_GRAPHISM_HPP
