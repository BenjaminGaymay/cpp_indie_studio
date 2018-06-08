//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// LocalGame
//

#include "Core.hpp"
#include "GameBackUp.hpp"
#include "LocalGame.hpp"

Indie::LocalGame::LocalGame()
{}

Indie::LocalGame::~LocalGame()
{}

void Indie::LocalGame::storeInformations()
{
	auto dropDownPlayer = static_cast<irr::gui::IGUIComboBox*>(m_gui->getRootGUIElement()->getElementFromId(GUI_ID_NB_PLAYER, true));
	auto dropDownAi = static_cast<irr::gui::IGUIComboBox*>(m_gui->getRootGUIElement()->getElementFromId(GUI_ID_NB_AI, true));
	auto selectedFile = static_cast<irr::gui::IGUIListBox*>(m_gui->getRootGUIElement()->getElementFromId(GUI_ID_LOCAL_MAPS, true));

	m_nbAi = std::stoi(ManageStrings::convertWchart(dropDownAi->getItem(dropDownAi->getSelected())));
	m_nbPlayers = std::stoi(ManageStrings::convertWchart(dropDownPlayer->getItem(dropDownPlayer->getSelected())));
	m_mapName = ManageStrings::convertWchart(selectedFile->getListItem(selectedFile->getSelected()));
	std::cout << "INFOS:\nai: " << m_nbAi << "\nplayers: " << m_nbPlayers << "\nmap: " << m_mapName << std::endl;
}

void Indie::LocalGame::init(irr::IrrlichtDevice *device)
{
	m_device = device;
	m_gui = m_device->getGUIEnvironment();
	m_sceneManager = m_device->getSceneManager();
	m_nbAi = 0;
	m_nbPlayers = 0;
	m_mapName = "";
}