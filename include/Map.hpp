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
		void load(std::unique_ptr<Graphism> &graphism);
		void newMap(const std::string &mapPath, const float &size, const float &y, std::unique_ptr<Graphism> &graphism);
		irr::scene::ISceneNode *putBlock(std::unique_ptr<Graphism> &graphism, int id, int i, int mulY, int j);
		bool emptyBlock(const irr::core::vector3df &position);
		std::map<irr::scene::ISceneNode *, irr::core::vector2di> &getUnderMap3d() { return _3dundermap; };
		std::map<irr::scene::ISceneNode *, irr::core::vector2di> &getMap3d() { return _3dmap; };
		std::vector<std::vector<int>> &getMap2d() { return _2dmap; };
		const float &getSize() const { return _size; };
		const float &getHeight() const { return _height; };
		void clear3dMap();
		void clear2dMap();
		static irr::core::vector3df position2dTo3d(const irr::core::vector2di &pos);
		irr::scene::ISceneNode *get3dBlock(const irr::core::vector2di &);
		irr::scene::ISceneNode *get3dBlock(const irr::core::vector3df &pos);
		irr::core::vector2di get2dBlock(const irr::core::vector3df &pos);
	private:
		std::size_t _max_height;
		std::size_t _max_width;
		float _size;
		float _height;
		std::vector<std::vector<int>> _2dmap;
		std::map<irr::scene::ISceneNode *, irr::core::vector2di> _3dmap;
		std::map<irr::scene::ISceneNode *, irr::core::vector2di> _3dundermap;
		void initMap(const std::string &map);
	};
}