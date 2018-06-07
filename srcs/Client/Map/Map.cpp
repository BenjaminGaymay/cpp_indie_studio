//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Map
//

#include <cstdlib>
#include "Map.hpp"
#include "ManageStrings.hpp"

Indie::Map::Map(std::vector<std::string> &map, const float &size,
	const float &y, std::unique_ptr<Indie::Graphism> &graphism)
{
	std::vector<std::string> oneLine;

	_max_height = 0;
 	_max_width = 0;
 	_size = size;
 	_height = y;
 	clear3dMap();
 	clear2dMap();
	for (auto &line : map) {
		std::vector<int> tmp;
		oneLine = ManageStrings::splitString(line, ' ');
		for (auto &nb : oneLine)
			tmp.push_back(std::stoi(nb));
		_2dmap.push_back(tmp);
		_max_width = (tmp.size() > _max_width ? tmp.size() : _max_width);
	}
	_max_height = _2dmap.size();
	if (graphism)
		load(graphism);
}

Indie::Map::~Map()
{}

void Indie::Map::clear3dMap()
{
	for (auto &block : _3dmap) {
		if (block.first)
			block.first->remove();
	}
	for (auto &block : _3dundermap) {
		if (block.first)
			block.first->remove();
	}
	_3dmap.clear();
	_3dundermap.clear();
}

void Indie::Map::clear2dMap()
{
	_2dmap.clear();
}

void Indie::Map::newMap(const std::string &mapPath, const float &size,
						const float &y,
						std::unique_ptr<Indie::Graphism> &graphism)
{
 	_max_height = 0;
 	_max_width = 0;
 	_size = size;
 	_height = y;
 	clear3dMap();
 	clear2dMap();
	initMap(mapPath);
	load(graphism);
}

void Indie::Map::initMap(const std::string &fileName)
{
	FILE *file = fopen(fileName.c_str(), "r");
	char *buffer = nullptr, *number = nullptr;
	std::size_t size = 0;

	if (!file)
		throw std::runtime_error("Error: can't open map.");
	while (getline(&buffer, &size, file) > 0) {
		std::vector<int> line;
		number = strtok(buffer, " ");
		while (number && *number != '\n' && *number != '\0') {
			line.push_back(std::stoi(number));
			number = strtok(nullptr, " ");
		}
		_2dmap.push_back(line);
		if (line.size() > _max_width) _max_width = line.size();
		if (!buffer) free(buffer);
		buffer = nullptr;
	}
	this->_max_height = _2dmap.size();
	if (!buffer) free(buffer);
	fclose(file);
}

irr::scene::ISceneNode *Indie::Map::putBlock(std::unique_ptr<Graphism> &core, int id, int x, int mulY, int z)
{
	irr::f32 cubeSize;
	auto block = core->createTexture(*core->getTexture(id), {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, false);
	cubeSize = core->resizeNode(block, _size);
	block->setPosition(irr::core::vector3df(
			static_cast<irr::f32>((x * cubeSize) - (((_max_width - 1) * cubeSize) / 2.0)),
			_height + (mulY * cubeSize),
			static_cast<irr::f32>((z * cubeSize) - (((_max_height -1) * cubeSize) / 2.0))));
	return block;
}

void Indie::Map::load(std::unique_ptr<Indie::Graphism> &graphism)
{
	_3dmap.clear();
	_3dundermap.clear();
	for (std::size_t i = 0; i < _2dmap.size(); ++i) {
		for (std::size_t j = 0; j < _2dmap[i].size(); ++j) {
			_3dundermap.insert(std::pair<irr::scene::ISceneNode *, irr::core::vector2di>
			        (putBlock(graphism, 2, (_max_height - 1) - i, -1, (_max_width - 1)- j), irr::core::vector2di(j, i)));
			if (graphism->getTexture(_2dmap[i][j]))
				_3dmap.insert(std::pair<irr::scene::ISceneNode *, irr::core::vector2di>
				        (putBlock(graphism, _2dmap[i][j], (_max_height - 1) - i, 0, (_max_width - 1) - j), irr::core::vector2di(j, i)));
		}
	}
}

// >>>> DANS UN OBJET ?
bool infequal(irr::core::vector3df one, irr::core::vector3df two)
{
	return  (one.X <= two.X && one.Y <= two.Y && one.Z <= two.Z);
}

bool inf(irr::core::vector3df one, irr::core::vector3df two)
{
	return  (one.X < two.X && one.Y < two.Y && one.Z < two.Z);
}

bool supequal(irr::core::vector3df one, irr::core::vector3df two)
{
	return  (one.X >= two.X && one.Y >= two.Y && one.Z >= two.Z);
}

// <<<<<

irr::core::vector3df Indie::Map::position2dTo3d(const irr::core::vector2di &pos)
{
	irr::core::vector3df result;

	result.X = pos.Y * 20.00f;
	result.Y = 100.00f;
	result.Z = pos.X * 20.00f;
	return result;
}

irr::core::vector2di Indie::Map::get2dBlock(const irr::core::vector3df &target)
{
	for (auto &block : _3dmap) {
		const auto &pos = block.first->getPosition();
		if (infequal(pos, target) && inf(target, pos + _size))
			return block.second;
	}
	throw std::logic_error("Bha, case non trouvé wtf");
}

irr::scene::ISceneNode *Indie::Map::get3dBlock(const irr::core::vector2di &target)
{
	for (auto &block : _3dmap) {
		const auto &pos = block.second;
		if (target.X == pos.X && target.Y == pos.Y)
			return block.first;
	}
	return nullptr;
}

irr::scene::ISceneNode *Indie::Map::get3dBlock(const irr::core::vector3df &target)
{
	for (auto &block : _3dmap) {
		const auto &pos = block.first->getPosition();
		if (infequal(pos, target) && inf(target, pos + _size))
			return block.first;
	}
	return nullptr;
}

bool Indie::Map::emptyBlock(const irr::core::vector3df &position)
{
	auto block = get3dBlock(position);
	if (!block) {
		return false;
	}
	return (!block->isVisible());
}