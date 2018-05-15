/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#include <stdio.h>
#include <zconf.h>
#include "Map.hpp"

Indie::Map::Map(const float &size, const float &y)
: _max_height(0), _max_width(0), _size(size), _height(y)
{
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
		_map.push_back(line);
		if (line.size() > _max_width) _max_width = line.size();
		if (!buffer) free(buffer);
		buffer = nullptr;
	}
	this->_max_height = _map.size();
	if (!buffer) free(buffer);
	fclose(file);
}

irr::scene::IAnimatedMeshSceneNode *Indie::Map::putBlock(Indie::Core &core, int id, int x, int mulY, int z)
{
	irr::f32 cubeSize;

	auto block = core.createTexture(*core.getTexture(id), {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, false);
	cubeSize = core.resizeNode(block, _size);
	std::cout << cubeSize << std::endl;
	block->setPosition(irr::core::vector3df(
			static_cast<irr::f32>((x * cubeSize) - (((_max_width - 1) *	cubeSize) / 2.0)),
			_height + (mulY * cubeSize),
			static_cast<irr::f32>((z * cubeSize) - (((_max_height - 1) * cubeSize) / 2.0))));
	return block;
}

void Indie::Map::load(Indie::Core &core)
{
	for (int i = 0; i < _map.size(); ++i)
		for (int j = 0; j < _map[i].size(); ++j) {
			m_u_cubes.push_back(putBlock(core, 2, i, -1, j));
			if (core.getTexture(_map[i][j]))
				m_cubes.push_back(putBlock(core, _map[i][j], i, 0, j));
		}
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> &Indie::Map::getMap3d()
{
	return m_cubes;
}

std::vector<std::vector<int>> &Indie::Map::getMap2d()
{
	return _map;
}