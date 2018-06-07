//
// EPITECH PROJECT, 2018
// student
// File description:
// 16/05/18
//

#pragma once

#include <map>
#include "Window.hpp"
#include "Object.hpp"

namespace Indie {
	class Graphism {
	public:
		using textureElem = std::pair<irr::io::path, irr::io::path>;
		explicit Graphism(Window *m_core);
		~Graphism();
		void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
		irr::f32 resizeNode(irr::scene::ISceneNode *node, const float &size);
		irr::scene::ISceneNode *createTexture(const textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale, bool collision);
		const textureElem *getTexture(const int &nb);
		void clearNode();
	private:
		void generateTextureMap();

		std::map<int, textureElem> _texturesMap;
		std::vector<irr::scene::ISceneNode *> _decors;
		Window *m_core;
	};
}

