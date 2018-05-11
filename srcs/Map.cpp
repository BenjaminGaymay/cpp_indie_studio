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

	int i = 0;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::cout << m_map.size() << ":" << line.size() << std::endl;
			if (line.size() > this->max_width)
				this->max_width = line.size();
			this->m_map.push_back(line);
		}
		this->max_height = this->m_map.size();
	} else
		throw std::runtime_error("Error: can't open map.");
}

void Indie::Map::createArena(irr::IrrlichtDevice *device)
{
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *scene = device->getSceneManager();
	irr::f32 cubeSize;

	irr::scene::IAnimatedMeshSceneNode *arena = scene->addAnimatedMeshSceneNode(
			scene->getMesh("assets/models/cube.md2"));
	cubeSize = arena->getBoundingBox().getExtent().X;
	arena->setMaterialTexture(0,
							  driver->getTexture("assets/models/2D/sand.jpg"));
	arena->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	arena->setPosition(irr::core::vector3df(0, 100 - cubeSize, 0));
	arena->setScale(irr::core::vector3df(21, 1, 22));
}

void Indie::Map::load(irr::IrrlichtDevice *device)
{
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *scene = device->getSceneManager();
	irr::f32 cubeSize;
	int h = 0;

	for (int i = 0; i < m_map.size(); ++i)
		for (int j = 0; j < m_map[i].size(); ++j) {
			if (m_map[i][j] == '#') {
				m_cubes.push_back(scene->addAnimatedMeshSceneNode(
						scene->getMesh("assets/models/cube.md2")));
				cubeSize = m_cubes[h]->getBoundingBox().getExtent().X;
				m_cubes[h]->setMaterialTexture(0, driver->getTexture("assets/models/crate.jpg"));
				m_cubes[h]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				m_cubes[h]->setPosition(irr::core::vector3df(
						static_cast<irr::f32>((i * cubeSize) - (((this->max_width - 1) * cubeSize) / 2.0)),
						100,
						static_cast<irr::f32>((j * cubeSize) - (((this->max_height - 1) * cubeSize) / 2.0))));
				++h;
			}
		}
	createArena(device);
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> Indie::Map::getMap() const
{
	return m_cubes;
}