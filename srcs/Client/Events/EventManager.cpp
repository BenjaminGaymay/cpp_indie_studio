/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventManager
*/


#include "EventManager.hpp"
#include "Core.hpp"

Indie::EventManager::EventManager()
{}

Indie::EventManager::~EventManager()
{}

Indie::EventManager::EventManager(Core *core) :
	m_core(core)
{}

void Indie::EventManager::init(Core *core)
{
	m_core = core;
}

void Indie::EventManager::manage()
{
	for (std::size_t id = 0; id < BTN_COUNT; id++) {
		if (m_core->getEvent().isButtonClicked(static_cast<IdGui>(id))) {
			switch (id) {
				case GUI_ID_QUIT_BUTTON:
					m_core->getWindow().m_device->closeDevice();
					break;
				case GUI_ID_PLAY_BUTTON:
					m_core->getMenu().m_main->setVisible(false);
					m_core->getMenu().m_play->setVisible(true);
					break;
				case GUI_ID_OPTIONS_BUTTON:
					m_core->getMenu().m_main->setVisible(false);
					m_core->getMenu().m_option->setVisible(true);
					break;
				case GUI_ID_MAP_BUTTON:
					m_core->getMenu().m_main->setVisible(false);
					m_core->getMenu().m_mapMenu->setVisible(true);
					break;
				case GUI_ID_MAP_BACK_BUTTON:
					m_core->getMenu().m_main->setVisible(true);
					m_core->getMenu().m_mapMenu->setVisible(false);
					break;
				case GUI_ID_PLAY_BACK_BUTTON:
					m_core->getMenu().m_main->setVisible(true);
					m_core->getMenu().m_play->setVisible(false);
					break;
				case GUI_ID_ROOM_BACK_BUTTON:
					m_core->getMenu().m_play->setVisible(true);
					if (m_core->getPlayerId() == 0)
						m_core->getMenu().m_roomS->setVisible(false);
					else
						m_core->getMenu().m_roomC->setVisible(false);
					break;
				case GUI_ID_OPTION_BACK_BUTTON:
					m_core->getMenu().m_main->setVisible(true);
					m_core->getMenu().m_option->setVisible(false);
					break;
				case GUI_ID_MAP_RANDOM_BUTTON:
					m_core->createRandMap("azerty.txt", 50, 50);
					//m_core->getMenu().m_mapEdit->setVisible(false);
					break;
				case GUI_ID_MAP_EDITOR_BUTTON:
					m_core->setAppState(MAPPING);//m_state = MAPPING;
					m_core->getMenu().m_mapMenu->setVisible(false);
					m_core->getMenu().m_mapEdit->setVisible(true);
					break;
				case GUI_ID_READY:
					m_core->setAppState(READY);
					if (m_core->getPlayerId() == 0)
						m_core->getMenu().m_roomS->setVisible(false);
					else
						m_core->getMenu().m_roomC->setVisible(false);
					break;
				case GUI_ID_PLAY_CLIENT:
					m_core->setAppState(CONNECT);
					//m_state = CONNECT;
					m_core->getMenu().m_roomC->setVisible(true);
					m_core->getMenu().m_play->setVisible(false);
					break;
				case GUI_ID_PLAY_SERVER:
				m_core->setAppState(LAUNCH_SERVER);
					// m_state = LAUNCH_SERVER;
					m_core->getMenu().m_roomS->setVisible(true);
					m_core->getMenu().m_play->setVisible(false);
					break;
				case GUI_ID_MAP_SAVE_BUTTON:
					m_core->getMenu().m_mapEdit->setVisible(false);
					m_core->getMenu().m_mapMenu->setVisible(true);
					m_core->setRun(false);
					break;
				case GUI_ID_DOWN_BUTTON:
					m_core->getMenu().m_down->setVisible(false);
					m_core->getMenu().m_main->setVisible(true);
					m_core->setAppState(MENU);
					// m_state = MENU;
					break;
				case GUI_ID_LEAVE_GAME_BUTTON:
					m_core->exitGame();
					m_core->setAppState(MENU);
					// m_state = MENU;
					m_core->getMenu().m_gameOptions->setVisible(false);
					m_core->getMenu().m_main->setVisible(true);
					break;
				case GUI_ID_QUIT_GAME_BUTTON:
					m_core->setRun(false);
					break;
				case GUI_ID_STAY_GAME_BUTTON:
					m_core->getMenu().m_gameOptions->setVisible(false);
					m_core->getWindow().getCamera().change(m_core->getWindow().getSceneManager(), Camera::FPS);
					m_core->getWindow().m_device->getCursorControl()->setVisible(false);
					break;
				default:
					break;
			}
		}
	}
}