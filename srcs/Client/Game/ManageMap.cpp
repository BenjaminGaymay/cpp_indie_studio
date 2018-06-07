//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ManageMap
//

#include "Core.hpp"
#include "Player.hpp"

void Indie::Core::comMap(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	switch (event) {
		case APPEAR: _mapper = std::make_unique<Map>(infos, 20.0f, 100.0f, _graphism); break;
		case DESTROYBLOCK: destroyBlock(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1]))); break;
		case CREATEBLOCK: createBlock(static_cast<PowerUpType>(std::stoi(infos[0])), irr::core::vector2di(std::stoi(infos[1]), std::stoi(infos[2]))); break;
		case TAKEBONUS: takeBonus(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1])), static_cast<PowerUpType >(std::stoi(infos[2]))); break;
		default: break;
	}
}

void Indie::Core::takeBonus(const irr::core::vector2di &pos, const PowerUpType &bonus)
{
	_engine->play2D("music/bonus.wav", false, false, false);
	switch (bonus) {
		case SPEED_UP : _playerObjects[0]->setSpeed(_playerObjects[0]->getSpeed() + 0.1f); std::cerr << "SPEEDUP" << std::endl; break ;
		case BOMB_UP : _playerObjects[0]->setBombNumber(_playerObjects[0]->getBombNumber() + 1); std::cerr << "BOMBUP" << std::endl; break;
		case FIRE_UP : _playerObjects[0]->setPower(_playerObjects[0]->getPower() + 1); std::cerr << "FIREUP" << std::endl; break ;
		case WALLPASS_UP : _playerObjects[0]->setWallUp(true) ; std::cerr << "WALLUP" << std::endl; break ;
		default: std::cerr << "DEFAULT:" << bonus << std::endl; break ;
	}
	findAndDestroyEntity(pos);
}

void Indie::Core::createBlock(const Indie::PowerUpType &bonus, const irr::core::vector2di &pos)
{
	destroyBlock(pos);
	auto block = _mapper->get3dBlock(pos);
	auto bonusBlock = _graphism->createTexture(*_graphism->getTexture(bonus), block->getPosition(), {0, 0, 0}, {2, 2 , 2}, true);
	_graphism->resizeNode(bonusBlock, _mapper->getSize());
	_graphism->getBonus().emplace_back(pos, bonusBlock);
}

bool Indie::Core::findAndDestroyEntity(const irr::core::vector2di &target)
{
	for (auto elem = _graphism->getBonus().begin() ; elem != _graphism->getBonus().end() ; ++elem) {
		auto &bonus = *elem;
		if (bonus.getPosition2d() == target) {
			bonus.getTexture()->remove();
			_graphism->getBonus().erase(elem);
			return true;
		}
	};
	return false;
}

void Indie::Core::destroyBlock(const irr::core::vector2di &target)
{
	auto &map = _mapper->getMap2d();
	map[target.Y][target.X] = 0;
	if (findAndDestroyEntity(target))
		return;
	auto block = _mapper->get3dBlock(target);
	block->setVisible(false);
	block->setName("");
}
