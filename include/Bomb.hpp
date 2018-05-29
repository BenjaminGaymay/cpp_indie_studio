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
		Bomb(const int &timeMax, const std::size_t &lenght, const irr::core::vector2di &pos2d) : _timeMax(std::time(nullptr) + timeMax), _lenght(lenght), _state(TICTAC), _pos2d(pos2d) {};
		~Bomb() {};
		bool tictac();
	private:
		enum BombState {
			BOOM,
			TICTAC
		};
		std::time_t _timeMax;
		std::size_t _lenght;
		BombState _state;
		irr::core::vector2di _pos2d;
	};
}

#endif //BOMBERMAN_BOMB_HPP
