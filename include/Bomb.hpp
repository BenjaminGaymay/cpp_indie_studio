/*
** EPITECH PROJECT, 2018
** student
** File description:
** 14/05/18
*/
#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include <ctime>
#include <irrlicht/IAnimatedMeshSceneNode.h>

namespace Indie {
	class Bomb {
	public:
		Bomb(int timeMax, int lenght);
		~Bomb();
		void setTexture(irr::scene::ISceneNode *texture);
		irr::scene::IAnimatedMeshSceneNode *getTexture();
		void fire(Player *player, std::unique_ptr<Map> &_mapper, std::unique_ptr<Graphism> &graphism);
		bool boom(Player *player, std::unique_ptr<Map> &map);
	private:
		// Renommer l'enum (genre BombState)
		enum State {
			BOOM,
			NONE
		};
		std::time_t _timeMax;
		int _lenght;
		bool _state;
		irr::scene::IAnimatedMeshSceneNode *_texture;
	};
}

#endif //BOMBERMAN_BOMB_HPP
