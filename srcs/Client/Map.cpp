/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#include <cstdio>
#include <Graphism.hpp>
#include "Map.hpp"

Indie::Map::Map(const std::string &mapPath, const float &size, const float &y, std::unique_ptr<Graphism> &graphism)
		: _max_height(0), _max_width(0), _size(size), _height(y)
{
	initMap(mapPath);
	load(graphism);
}

Indie::Map::~Map()
{}

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
			line.push_back(atoi(number));
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

	auto block = core->createTexture(*core->getTexture(id), {0, 0, 0}, {0, 0, 0},
									{1, 1, 1}, false);
	cubeSize = core->resizeNode(block, _size);
	block->setPosition(irr::core::vector3df(
			static_cast<irr::f32>((x * cubeSize) - (((_max_width - 1) * cubeSize) / 2.0)),
			_height + (mulY * cubeSize),
			static_cast<irr::f32>((z * cubeSize) - (((_max_height -1) * cubeSize) / 2.0))));
	return block;
}

void Indie::Map::load(std::unique_ptr<Graphism> &core)
{
	for (int i = 0; i < _2dmap.size(); ++i)
		for (int j = 0; j < _2dmap[i].size(); ++j) {
			_3dundermap.push_back(putBlock(core, 2, i, -1, j));
			if (core->getTexture(_2dmap[i][j]))
				_3dmap.push_back(putBlock(core, _2dmap[i][j], i, 0, j));
		}
}

std::vector<irr::scene::ISceneNode *> &Indie::Map::getMap3d()
{
	return _3dmap;
}

std::vector<std::vector<int>> &Indie::Map::getMap2d()
{
	return _2dmap;
}

const float &Indie::Map::getSize() const
{
	return _size;
}

const float &Indie::Map::getHeight() const
{
	return _height;
}

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

irr::scene::ISceneNode *Indie::Map::get3dBlock(const irr::core::vector3df &target)
{
	std::cout << "ENTRE" << std::endl;
	for (auto &block : _3dmap) {
		const auto &pos = block->getPosition();
		if (infequal(pos, target) && inf(target, pos + 20)) {
			return block;
		}
	}
	std::cout << "SORTIE" << std::endl;
	return nullptr;
}