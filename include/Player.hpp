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
	class ObjectPlayer {
		public:
			ObjectPlayer(int id, irr::scene::IAnimatedMeshSceneNode *node): _id(id), _player(node) {}
			void setPosition(irr::core::vector3df &pos) { _player->setPosition(pos); }
			irr::core::vector3df getPosition() { return _player->getPosition(); }
			int _id;
			irr::scene::IAnimatedMeshSceneNode *_player;
	};

	class Player {
	public:
		explicit Player(irr::scene::IAnimatedMeshSceneNode *node);
		Player(int, irr::scene::IAnimatedMeshSceneNode *);
		~Player();
		irr::core::vector3df move(const Events &event);
		irr::scene::IAnimatedMeshSceneNode *getPlayer();
		irr::core::vector3df getPosition() { return _player->getPosition(); }
		void setPosition(irr::core::vector3df &pos) { _player->setPosition(pos); }
		static void rotationWithMove(irr::scene::IAnimatedMeshSceneNode *node, const irr::core::vector3df &newPosition);
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
