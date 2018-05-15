/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#pragma once

#include <vector>
#include <map>
#include "Socket.hpp"
#include "Window.hpp"

namespace Indie {
	class Player;
	class ObjectPlayer;

	class Core {
	public:
		using textureElem = std::pair<irr::io::path, irr::io::path>;
		Core();

		~Core();
		void run();
		void drawCaption(int &);
		void buildDecor();
		void createWater(irr::core::vector3df position,  irr::core::vector3df rotation);
		void createArena();
		 irr::scene::IAnimatedMeshSceneNode *createTexture(const textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale, bool collision);
		irr::scene::IAnimatedMeshSceneNode *createIsland(irr::core::vector3df position, irr::core::vector3df rotation);
		void setCollision(irr::scene::ISceneNode *wall, irr::scene::ISceneNode *target);
		void processEvents(const Events &);
		const textureElem &getTexture(const int &nb);
		int waitForId();
		void readServerInformations(std::vector<std::string> &);
		void addPlayer(int, irr::core::vector3df &);
		void removePlayer(int, irr::core::vector3df &);
		void movePlayer(int, irr::core::vector3df &);
	private:
		void generateTextureMap();
		/* FIRST object, SECOND texture */
		std::map<int, textureElem> _texturesMap;
		std::vector<irr::scene::IAnimatedMeshSceneNode *> _nodesList;
		Window m_core;
		bool m_run;
		std::vector<std::unique_ptr<Player>> _playerObjects;
		std::unique_ptr<Socket> _socket;
		std::vector<void (Indie::Core::*)(int, irr::core::vector3df &)> _playersFct;
	};
}