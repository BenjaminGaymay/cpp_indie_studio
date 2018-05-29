//
// EPITECH PROJECT, 2018
// student
// File description:
// 13/05/18
//

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "Core.hpp"

namespace Indie {
	class Player {
	public:
		explicit Player(int id, irr::scene::ISceneNode *, s_tchat &);
		~Player();
		irr::core::vector3df move(Events &event);
		irr::scene::IAnimatedMeshSceneNode *getPlayer();
		void rotationWithMove(irr::scene::ISceneNode *node, const irr::core::vector3df &newPosition);
		bool isStanding();
		void setStanding(bool state);
		void setSpeed(float speed);
		void setPower(std::size_t power);
		std::size_t getPower();
		void setPos2d(const irr::core::vector2di &pos) { _pos2d = pos;}
		const float &getSpeed();
		irr::core::vector3df getPosition() { return _player->getPosition(); }
		irr::core::vector3df getRotation() { return _player->getRotation(); }
		void setPosition(const irr::core::vector3df &pos) { _player->setPosition(pos); }
		void setId(int id) { _id = id; }
		int getId() { return _id; }
	private:
		int _id;
		bool _stand;
		irr::scene::IAnimatedMeshSceneNode *_player;
		irr::f32 _speed;
		s_tchat _tchat;
		irr::core::vector2di _pos2d;
		std::size_t _power;
	protected:
	};
}

#endif //BOMBERMAN_PLAYER_HPP
