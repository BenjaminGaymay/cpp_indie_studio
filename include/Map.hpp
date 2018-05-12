/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <vector>
#include <iostream>
#include <fstream>

namespace Indie {
	class Map {
	public:
		Map();
		~Map();
		void initMap(const std::string &map);
		void load(irr::IrrlichtDevice *device);
		void createArena(irr::IrrlichtDevice *device);
		std::vector<irr::scene::IAnimatedMeshSceneNode*> getMap() const;

	private:
		std::size_t _max_width;
		std::size_t _max_height;
		std::vector<std::vector<int>> _map;
		std::vector<irr::scene::IAnimatedMeshSceneNode *> m_cubes;
	};
}