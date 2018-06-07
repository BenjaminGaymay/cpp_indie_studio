/*
** EPITECH PROJECT, 2018
** student
** File description:
** 07/06/18
*/
#pragma once

#include "Map.hpp"

namespace Indie {
	class Game {
	public:
		Game() : _mapper(std::make_unique<Map>()) {};
		~Game() = default;
		bool findAndDestroyEntity(const irr::core::vector2di &target);
		std::vector<Indie::Object> &getBombs() { return _bombs; };
		std::vector<Indie::Object> &getBonus() { return _bonus; };
		std::unique_ptr<Map> &getMapperEdit() { return _mapper; };
		void setMapper(std::unique_ptr<Map> mapper) {
			if (_mapper) {
				_mapper.release();
				_mapper.reset();
				_mapper = nullptr;
			}
			_mapper = std::move(mapper);
		};
		void clear2dMap();
		void clear3dMap();
		void clearMaps();
	private:
		std::unique_ptr<Map> _mapper;
		std::vector<Indie::Object> _bombs;
		std::vector<Indie::Object> _bonus;
	};
}