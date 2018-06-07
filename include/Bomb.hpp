//
// EPITECH PROJECT, 2018
// student
// File description:
// 14/05/18
//
#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include <chrono>
#include <vector2d.h>
#include <IAnimatedMeshSceneNode.h>

namespace Indie {
	class Bomb {
	public:
		enum BombState {
			BOOM,
			TICTAC
		};
		Bomb(const int &timeMax, const std::size_t &power, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos3d, const int &id)
				: _timeMax(std::time(nullptr) + timeMax), _timeMaxInit(timeMax), _power(power), _pos2d(pos2d), _pos3d(pos3d), _id(id),  _state(TICTAC) {};
		~Bomb() = default;
		bool tictac() {
			if (_state == TICTAC && std::time(nullptr) >= _timeMax)
				_state = BOOM;
			return _state;
		};
		const Indie::Bomb::BombState &getState() const { return _state; };
		const irr::core::vector2di &getPos2d() const { return _pos2d; };
		const irr::core::vector3df &getPos3d() const { return _pos3d; };
		const std::size_t &getPower() const { return _power; };
		const int &getId() const { return _id; };
		void setPower(const std::size_t &power) { _power = power; };
		const int &getTimeMax() const { return _timeMaxInit; };
	private:
		std::time_t _timeMax;
		int _timeMaxInit;
		std::size_t _power;
		irr::core::vector2di _pos2d;
		irr::core::vector3df _pos3d;
		int _id;
		BombState _state;
	};
}

#endif //BOMBERMAN_BOMB_HPP
