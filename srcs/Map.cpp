/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#include <stdio.h>
#include <zconf.h>
#include "Map.hpp"

Indie::Map::Map()
: _max_height(0), _max_width(0)
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

void Indie::Map::load(Indie::Core &core)
{
	int h = 0;

	for (int i = 0; i < _map.size(); ++i)
		for (int j = 0; j < _map[i].size(); ++j) {
			if (_map[i][j] == 0) {
				m_cubes.push_back(core.createTexture(core.getTexture(0), {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, false));
				const irr::f32 cubeSize = (m_cubes[h]->getBoundingBox().getExtent().Z) * m_cubes[h]->getScale().X;
				std::cout << cubeSize << std::endl;
				m_cubes[h]->setPosition(irr::core::vector3df(
						static_cast<irr::f32>((i * cubeSize) - (((_max_width - 1) *	cubeSize) / 2.0)),
						100,
						static_cast<irr::f32>((j * cubeSize) - (((_max_height - 1) * cubeSize) / 2.0))));
				++h;
			}
		}
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> Indie::Map::getMap() const
{
	return m_cubes;
}