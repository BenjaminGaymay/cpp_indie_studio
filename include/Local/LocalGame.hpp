//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// LocalGame
//

#pragma once

namespace Indie
{
	class LocalGame {
	public:
		LocalGame();
		~LocalGame();
		void init(irr::IrrlichtDevice *);
		void storeInformations();

	private:
		std::size_t m_nbAi;
		std::size_t m_nbPlayers;
		std::string m_mapName;

		irr::IrrlichtDevice *m_device;
		irr::gui::IGUIEnvironment *m_gui;
		irr::scene::ISceneManager *m_sceneManager;
	};
}