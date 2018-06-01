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
		explicit Player(const int &id, irr::scene::ISceneNode *, s_tchat &);
		~Player();
		irr::core::vector3df move(Events &event);
		irr::scene::IAnimatedMeshSceneNode *getPlayer() { return _player; };
		void rotationWithMove(irr::scene::ISceneNode *node, const irr::core::vector3df &newPosition);
		const bool &isStanding() { return _stand; };
		void setStanding(const bool &state) { _stand = state; };
		void setSpeed(const float &speed) { _speed = speed; };
		void setPower(const std::size_t &power) { _power = power; };
		const std::size_t &getPower() const { return _power; };
		const std::size_t &getBombNumber() const { return _bombNumber; };
		void setBombNumber(const std::size_t bombNumber) { _bombNumber = bombNumber; };
		void setPos2d(const irr::core::vector2di &pos) { _pos2d = pos;}
		const float &getSpeed() const { return _speed; };
		const irr::core::vector3df &getPosition() const  { return _player->getPosition(); };
		const irr::core::vector3df &getRotation() const { return _player->getRotation(); };
		void setPosition(const irr::core::vector3df &pos) { _player->setPosition(pos); };
		void setId(int id) { _id = id; }
		const int &getId() const { return _id; }
		void setWallUp(const bool &wallUp) { _wallUp = wallUp; };
		const bool &getWallUp() const { return _wallUp; };
	private:
		int _id;
		bool _stand;
		irr::scene::IAnimatedMeshSceneNode *_player;
		irr::f32 _speed;
		s_tchat _tchat;
		irr::core::vector2di _pos2d;
		std::size_t _power;
		std::size_t _bombNumber;
		bool _wallUp;
	protected:
	};
}

#endif //BOMBERMAN_PLAYER_HPP
