/*
** EPITECH PROJECT, 2018
** student
** File description:
** 13/05/18
*/
#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include <irrlicht/IAnimatedMeshSceneNode.h>
#include <memory>
#include "Core.hpp"

namespace Indie {
	class Player {
	public:
		explicit Player(irr::scene::IAnimatedMeshSceneNode *node);
		~Player();
		void move(const Events &event);
		irr::scene::IAnimatedMeshSceneNode *getPlayer();
		void rotationWithMove(irr::scene::IAnimatedMeshSceneNode *node, const irr::core::vector3df &newPosition);
		bool isStanding();
		void setStanding(bool state);
	private:
		irr::f32 _speed;
		irr::scene::IAnimatedMeshSceneNode *_player;
		bool _stand;
	protected:
	};
}

#endif //BOMBERMAN_PLAYER_HPP
