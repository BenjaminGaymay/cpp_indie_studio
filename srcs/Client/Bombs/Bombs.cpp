//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Bombs
//

#include "Core.hpp"

void Indie::Core::comBomb(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	try {
		auto id = std::stoi(infos[0]);

		switch (event) {
			case CREATEBOMB: dropBomb(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stoi(infos[4]), std::stof(infos[5])), std::stoul(infos[6])); break;
			case DESTROYBOMB: destroyBomb(irr::core::vector2di(std::stoi(infos[0]), std::stoi(infos[1]))); break;
			default: break;
		}
	} catch (const std::exception &e) {}
}

void Indie::Core::dropBomb(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos3d, const std::size_t &power)
{
	auto &mapper = _game->getMapperEdit();
	(void) id;
	(void) pos2d;
	(void) power;
	auto block = mapper->get3dBlock(pos3d + mapper->getSize() / 2);
	auto bomb = _graphism->createTexture(*_graphism->getTexture(3), block->getPosition(), {0, 0, 0}, {2, 2, 2}, true);
	_graphism->resizeNode(bomb, mapper->getSize());
	_game->getBombs().emplace_back(pos2d, bomb);

}

void Indie::Core::destroyBomb(const irr::core::vector2di &target)
{
	auto &bombs = _game->getBombs();

	for (auto elem = bombs.begin() ; elem != bombs.end() ; ++elem) {
		auto &bomb = *elem;
		if (bomb.getPosition2d() == target) {
			_engine->play2D("music/boom.wav", false, false, false);
			bomb.getTexture()->remove();
			bombs.erase(elem);
			return ;
		}
	}
}
