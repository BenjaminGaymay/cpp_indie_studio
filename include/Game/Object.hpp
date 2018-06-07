//
// EPITECH PROJECT, 2018
// student
// File description:
// 29/05/18
//

#pragma once

#include <ISceneNode.h>

namespace Indie {
	class Object {
	public:
		Object(const irr::core::vector2di &pos2d, irr::scene::ISceneNode *_texture)
		: _pos2d(pos2d), _texture(_texture) {};
		~Object() = default;
		irr::scene::ISceneNode *getTexture() { return _texture; };
		irr::core::vector2di &getPosition2d() { return _pos2d; };
	private:
		irr::core::vector2di _pos2d;
		irr::scene::ISceneNode *_texture;
	};
}
