//
// EPITECH PROJECT, 2018
// student
// File description:
// 13/05/18
//

#pragma once

#include "Core.hpp"

namespace Indie {
	class Player {
	public:
		Player(const int &id, irr::scene::IAnimatedMeshSceneNode *, Chat &);
		~Player();
		irr::core::vector3df move(Events &event, std::unique_ptr<Socket> &_socket);
		irr::scene::IAnimatedMeshSceneNode *getPlayer() { return _player; };
		void setPlayer(irr::scene::IAnimatedMeshSceneNode *player) { _player = player; };
		void rotationWithMove(irr::scene::ISceneNode *node, const irr::core::vector3df &newPosition);
		const bool &isStanding() { return _stand; };
		void setStanding(const bool &state) { _stand = state; };
		void setSpeed(const float &speed) { _speed = speed; };
		void setPower(const std::size_t &power) { _power = power; };
		const std::size_t &getPower() const { return _power; };
		const std::size_t &getBombNumber() const { return _bombNumber; };
		void setBombNumber(const std::size_t bombNumber) { if (_bombNumber < 10) _bombNumber = bombNumber; };
		void setPos2d(const irr::core::vector2di &pos) { _pos2d = pos;}
		const float &getSpeed() const { return _speed; };
		const irr::core::vector3df &getPosition() const  { return _player->getPosition(); };
		const irr::core::vector3df &getRotation() const { return _player->getRotation(); };
		void setPosition(const irr::core::vector3df &pos) { _player->setPosition(pos); };
		void setId(int id) { _id = id; }
		const int &getId() const { return _id; }
		void setWallUp(const bool &wallUp) { _wallUp = wallUp; };
		const bool &getWallUp() const { return _wallUp; };
		void setAlive(const bool &alive) { _alive = alive; };
		const bool &isAlive() { return _alive; };
		void setState(const ObjectsEvents &state) { _state = state; };
		const ObjectsEvents &getState() { return _state; };
	private:
		int _id;
		bool _stand;
		irr::scene::IAnimatedMeshSceneNode *_player;
		irr::f32 _speed;
		Chat _chat;
		irr::core::vector2di _pos2d;
		std::size_t _power;
		std::size_t _bombNumber;
		bool _wallUp;
		bool _alive;
		ObjectsEvents _state;
	protected:
	};
}