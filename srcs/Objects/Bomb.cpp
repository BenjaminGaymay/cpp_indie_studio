/*
** EPITECH PROJECT, 2018
** student
** File description:
** 14/05/18
*/

#include <chrono>
#include <iostream>
#include "Bomb.hpp"

Indie::Bomb::Bomb(int timeMax, int lenght)
		: _timeMax(std::time(nullptr) + timeMax), _lenght(lenght), _state(false)
{}

Indie::Bomb::~Bomb()
{}

bool Indie::Bomb::boom()
{
	if (!_state && std::time(nullptr) >= _timeMax) {
		_state = true;
		_texture->remove();
	}
	return _state;
}

void Indie::Bomb::setTexture(irr::scene::IAnimatedMeshSceneNode *texture)
{
	_texture = texture;
}

irr::scene::IAnimatedMeshSceneNode* Indie::Bomb::getTexture()
{
	return _texture;
}