/*
** EPITECH PROJECT, 2018
** student
** File description:
** 07/06/18
*/

#include "Game.hpp"

bool Indie::Game::findAndDestroyEntity(const irr::core::vector2di &target)
{
	for (auto elem = _bonus.begin() ; elem != _bonus.end() ; ++elem) {
		auto &bonus = *elem;
		if (bonus.getPosition2d() == target) {
			bonus.getTexture()->remove();
			_bonus.erase(elem);
			return true;
		}
	};
	return false;
}

void Indie::Game::clear3dMap()
{
	for (auto block : _bonus)
		if (block.getTexture())
			block.getTexture()->remove();
	_bonus.clear();
	for (auto block : _bombs)
		if (block.getTexture())
			block.getTexture()->remove();
	_bombs.clear();
	if (_mapper)
		_mapper->clear3dMap();
}

void Indie::Game::clear2dMap()
{
	if (_mapper)
		_mapper->clear2dMap();
}

void Indie::Game::clearMaps()
{
	clear3dMap();
	clear2dMap();
}
