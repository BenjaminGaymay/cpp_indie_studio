/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#include "Map.hpp"

Indie::Map::Map()
{
	this->max_height = 0;
	this->max_width = 0;
}

Indie::Map::~Map()
{}

void Indie::Map::initMap(const std::string &fileName)
{
	std::fstream file(fileName);
	std::string line;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			if (line.size() > this->max_width)
				this->max_width = line.size();
			this->m_map.push_back(line);
		}
		this->max_height = this->m_map.size();
	} else
		throw std::runtime_error("Error: can't open map.");
}

void Indie::Map::load(irr::IrrlichtDevice *device)
{
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *scene = device->getSceneManager();
	irr::f32 cubeSize;
	int h = 0;

	for (int i = 0; i < m_map.size(); i++)
		for (int j = 0; j < m_map[i].size(); j++) {
			if (m_map[i][j] == '#') {
				m_cubes.push_back(scene->addAnimatedMeshSceneNode(scene->getMesh("assets/models/cube.md2")));
				cubeSize = m_cubes[h]->getBoundingBox().getExtent().X;
				m_cubes[h]->setMaterialTexture(0, driver->getTexture("assets/models/crate.jpg"));
				m_cubes[h]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				m_cubes[h]->setPosition(irr::core::vector3df((i * cubeSize) - ((this->max_height * cubeSize) / 2), 100, (j * cubeSize) - ((this->max_width * cubeSize) / 2)));
				h++;
			}
		}

}

std::vector<irr::scene::IAnimatedMeshSceneNode*> Indie::Map::getMap() const
{
	return m_cubes;
}