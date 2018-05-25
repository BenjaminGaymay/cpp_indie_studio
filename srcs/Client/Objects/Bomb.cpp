//
// EPITECH PROJECT, 2018
// student
// File description:
// 14/05/18
//

//#include <chrono>
//#include <iostream>
#include <Player.hpp>
#include "Bomb.hpp"

// std::vector<Bomb> bombs;
// if (m_event.isKeyDown(irr::KEY_SPACE)) {
// 				Indie::Bomb bomb(2, 10);
// 				bomb.setTexture(_graphism->createTexture(*_graphism->getTexture(3), _playerObjects[0]->getPosition(), {0, 0, 0}, {100, 100, 100}, false));
// 				bombs.push_back(bomb);
// 			}
// 			bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Indie::Bomb &row) {return row.boom();}), bombs.end());

Indie::Bomb::Bomb(int timeMax, int lenght)
		: _timeMax(std::time(nullptr) + timeMax), _lenght(lenght), _state(false)
{}

Indie::Bomb::~Bomb()
{}

bool Indie::Bomb::boom(Player *player, std::unique_ptr<Map> &map)
{
	(void)player;
	(void)map;
	if (!_state && std::time(nullptr) >= _timeMax) {
		_state = true;
		_texture->remove();
	}
	return _state;
}

//
// @arg power power of explosion
// @brief permet de faire apparaitre une ligne de texture (genre pour l'eplosion)
// @brief la generation de ces block s'arrête quand il y a un mur.
//
void Indie::Bomb::fire(Player *player, std::unique_ptr<Map> &_mapper, std::unique_ptr<Graphism> &graphism)
{
	int power = 5;
	auto scale = _mapper->getSize();
	auto position = player->getPosition();
	for (int  i = power; i < power; ++i) {
		auto target = irr::core::vector3df(position + irr::core::vector3df(position.X + (i * scale), 0, 0));
		if (!_mapper->emptyBlock(target))
			break ;
		auto fire = graphism->createTexture(*graphism->getTexture(4), target, {0, 0, 0}, {2, 2, 2}, true);
		graphism->resizeNode(fire, _mapper->getSize());
	}
	for (int  i = power; i > 0; --i) {
		auto target = irr::core::vector3df(position + irr::core::vector3df(position.X + (i * scale), 0, 0));
		if (!_mapper->emptyBlock(target))
			break ;
		auto fire = graphism->createTexture(*graphism->getTexture(4), target, {0, 0, 0}, {2, 2, 2}, true);
		graphism->resizeNode(fire, _mapper->getSize());
	}
	for (int  i = power; i < power; ++i) {
		auto target = irr::core::vector3df(position + irr::core::vector3df(0, 0, position.Z + (i * scale)));
		if (!_mapper->emptyBlock(target))
			break ;
		auto fire = graphism->createTexture(*graphism->getTexture(4), target, {0, 0, 0}, {2, 2, 2}, true);
		graphism->resizeNode(fire, _mapper->getSize());
	}
	for (int  i = power; i > 0; --i) {
		auto target = irr::core::vector3df(position + irr::core::vector3df(0, 0, position.Z + (i * scale)));
		if (!_mapper->emptyBlock(target))
			break ;
		auto fire = graphism->createTexture(*graphism->getTexture(4), target, {0, 0, 0}, {2, 2, 2}, true);
		graphism->resizeNode(fire, _mapper->getSize());
	}
}

void Indie::Bomb::setTexture(irr::scene::ISceneNode *texture)
{
	_texture = dynamic_cast<irr::scene::IAnimatedMeshSceneNode *>(texture);
}

irr::scene::IAnimatedMeshSceneNode* Indie::Bomb::getTexture()
{
	return _texture;
}