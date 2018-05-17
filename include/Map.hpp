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
#include "Graphism.hpp"

namespace Indie {
	class Map {
	public:
		Map(const std::string &mapPath, const float &size, const float &y, std::unique_ptr<Indie::Graphism> &graphism);
		~Map();
		void initMap(const std::string &map);
		void load(std::unique_ptr<Indie::Graphism> &core);
		irr::scene::ISceneNode *putBlock(std::unique_ptr<Indie::Graphism> &core, int id, int i, int mulY, int j);
		std::vector<irr::scene::ISceneNode*> &getMap3d();
		std::vector<std::vector<int>> &getMap2d();
		const float &getSize() const;
		const float &getHeight() const;
		irr::scene::ISceneNode *get3dBlock(const irr::core::vector3df &pos);

	private:
		std::size_t _max_width;
		std::size_t _max_height;
		const float _size;
		const float _height;
		std::vector<std::vector<int>> _2dmap;
		std::vector<irr::scene::ISceneNode *> _3dmap;
		std::vector<irr::scene::ISceneNode *> _3dundermap;
	};
}