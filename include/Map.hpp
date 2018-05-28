//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Map
//

#pragma once

#include <fstream>
#include "Graphism.hpp"

namespace Indie {
	class Map {
	public:
		Map() {}
		Map(std::vector<std::string> &, const float &,
			const float &, std::unique_ptr<Indie::Graphism> &);
		~Map();
		void initMap(const std::string &map);
		void load(std::unique_ptr<Graphism> &core);
		void newMap(const std::string &mapPath, const float &size, const float &y, std::unique_ptr<Graphism> &graphism);
		void clear2dMap();
		void clear3dMap();
		irr::scene::ISceneNode *putBlock(std::unique_ptr<Graphism> &core, int id, int i, int mulY, int j);
		bool emptyBlock(const irr::core::vector3df &position);
		std::vector<irr::scene::ISceneNode*> &getMap3d();
		std::vector<std::vector<int>> &getMap2d();
		const float &getSize() const;
		const float &getHeight() const;
		irr::scene::ISceneNode *get3dBlock(const irr::core::vector3df &pos);

	private:
		std::size_t _max_height;
		std::size_t _max_width;
		float _size;
		float _height;
		std::vector<std::vector<int>> _2dmap;
		std::vector<irr::scene::ISceneNode *> _3dmap;
		std::vector<irr::scene::ISceneNode *> _3dundermap;
	};
}