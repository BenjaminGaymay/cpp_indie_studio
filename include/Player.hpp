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
		irr::core::vector3df getPosition() { return _player->getPosition(); }
		void setPosition(irr::core::vector3df &pos) { _player->setPosition(pos); }
		void rotationWithMove(irr::scene::IAnimatedMeshSceneNode *node, const irr::core::vector3df &newPosition);
		bool isStanding();
		void setStanding(bool state);
		void setId(int id) { _id = id; }
		int getId() { return _id; }
	private:
		irr::f32 _speed;
		irr::scene::IAnimatedMeshSceneNode *_player;
		bool _stand;
		int _id;
	protected:
	};
}

#endif //BOMBERMAN_PLAYER_HPP
