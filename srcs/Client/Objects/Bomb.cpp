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

/**
 * @arg power power of explosion
 * @brief permet de faire apparaitre une ligne de texture (genre pour l'eplosion)
 * @brief la generation de ces block s'arrête quand il y a un mur.
 * @brief cette exemple ne s'occupe que de l'AXE X
 */
/*void save(Player *player, int power)
{
	auto scale = _mapper->getSize();
	auto position = player->getPosition();
	for (int  i = power; i < power; ++i) {
		auto target = irr::core::vector3df(position + irr::core::vector3df(position.X + (i * scale), 0, 0));
		if (!_mapper->emptyBlock(target))
			break ;
		auto fire = _graphism->createTexture(*_graphism->getTexture(4), target, {0, 0, 0}, {2, 2, 2}, true);
		_graphism->resizeNode(fire, _mapper->getSize());
	}
}*/

void Indie::Bomb::setTexture(irr::scene::IAnimatedMeshSceneNode *texture)
{
	_texture = texture;
}

irr::scene::IAnimatedMeshSceneNode* Indie::Bomb::getTexture()
{
	return _texture;
}