//
// EPITECH PROJECT, 2018
// student
// File description:
// 14/05/18
//
#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include <chrono>
#include <irrlicht/vector2d.h>
#include <irrlicht/IAnimatedMeshSceneNode.h>

namespace Indie {
	class Bomb {
	public:
		enum BombState {
			BOOM,
			TICTAC
		};
		Bomb(const int &timeMax, const std::size_t &power, const irr::core::vector2di &pos2d)
				: _timeMax(std::time(nullptr) + timeMax), _power(power), _pos2d(pos2d), _state(TICTAC) {};
		~Bomb() = default;
		bool tictac() {
			if (_state == TICTAC && std::time(nullptr) >= _timeMax)
				_state = BOOM;
			return _state;
		};
		const Indie::Bomb::BombState &getState() const { return _state; };
		const irr::core::vector2di &getPosition() const { return _pos2d; };
		const std::size_t &getPower() const { return _power; };
		void setPower(const std::size_t &power) { _power = power; };
	private:
		std::time_t _timeMax;
		std::size_t _power;
		irr::core::vector2di _pos2d;
		BombState _state;
	};
}

#endif //BOMBERMAN_BOMB_HPP
