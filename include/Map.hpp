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
#include "Core.hpp"

namespace Indie {
	class Map {
	public:
		Map();
		~Map();
		void initMap(const std::string &map);
		void load(Indie::Core &core);
		std::vector<irr::scene::IAnimatedMeshSceneNode*> &getMap3d();
		std::vector<std::vector<int>> &getMap2d();

	private:
		std::size_t _max_width;
		std::size_t _max_height;
		std::vector<std::vector<int>> _map;
		std::vector<irr::scene::IAnimatedMeshSceneNode *> m_cubes;
	};
}