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

void Indie::EventManager::checkMapNameValid()
{
	irr::gui::IGUIEditBox *edit = static_cast<irr::gui::IGUIEditBox *>(m_core->m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_MAP_NAME , true));
	std::string name = ManageStrings::convertWchart(edit->getText());

	if (name.empty())
		return;
	m_core->m_state = MAPPING;//m_state = MAPPING;
	m_core->m_menu.m_mapMenu->setVisible(false);
	m_core->m_menu.m_mapEdit->setVisible(true);
}

void Indie::EventManager::updateIpInput(irr::s32 id)
{
	irr::gui::IGUIButton *btn = static_cast<irr::gui::IGUIButton *>(m_core->m_core.m_gui->getRootGUIElement()->getElementFromId(id, true));
	irr::gui::IGUIEditBox *edit = static_cast<irr::gui::IGUIEditBox *>(m_core->m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_IP , true));
	std::string entered = ManageStrings::convertWchart(btn->getText());
	std::string current = ManageStrings::convertWchart(edit->getText());

	if (entered == "DEL") {
		if (current.size() > 0)
			current.pop_back();
	} else {
		if (current.size() < 15)
		current = std::string(current + entered);
	}
	edit->setText(std::wstring(current.begin(), current.end()).c_str());
}

void Indie::EventManager::manage(irrklang::ISoundEngine *engine)
{
	bool sound = true;

	for (std::size_t id = 101; id < 101 + BTN_COUNT; id++) {
		if (m_core->m_event.isButtonClicked(static_cast<IdGui>(id - 101))) {
			switch (id) {
				case GUI_ID_QUIT_BUTTON:
					m_core->m_core.m_device->closeDevice();
					break;
				case GUI_ID_PLAY_BUTTON:
					m_core->m_menu.m_main->setVisible(false);
					m_core->m_menu.m_play->setVisible(true);
					m_core->m_menu.chooseMap(GUI_ID_LIST_MAP);
					m_core->m_menu.chooseMap(GUI_ID_LOCAL_MAPS);
					break;
				case GUI_ID_OPTIONS_BUTTON:
					m_core->m_menu.m_main->setVisible(false);
					m_core->m_menu.m_option->setVisible(true);
					break;
				case GUI_ID_MAP_BUTTON:
					m_core->m_menu.m_main->setVisible(false);
					m_core->m_menu.m_mapMenu->setVisible(true);
					break;
				case GUI_ID_MAP_BACK_BUTTON:
					m_core->m_menu.m_main->setVisible(true);
					m_core->m_menu.m_mapMenu->setVisible(false);
					break;
				case GUI_ID_PLAY_BACK_BUTTON:
					m_core->m_menu.m_main->setVisible(true);
					m_core->m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_ROOM_BACK_BUTTON:
					m_core->m_menu.m_play->setVisible(true);
					if (m_core->_playerId == 0)
						m_core->m_menu.m_roomS->setVisible(false);
					else
						m_core->m_menu.m_roomC->setVisible(false);
					break;
				case GUI_ID_OPTION_BACK_BUTTON:
					m_core->m_menu.m_main->setVisible(true);
					m_core->m_menu.m_option->setVisible(false);
					break;
				case GUI_ID_MAP_RANDOM_BUTTON:
					{
						irr::gui::IGUIEditBox *edit = static_cast<irr::gui::IGUIEditBox *>(m_core->m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_MAP_NAME , true));
						std::string name = ManageStrings::convertWchart(edit->getText());
						if (!name.empty())
							m_core->createRandMap(name, 25, 25);
					}
					break;
				case GUI_ID_MAP_EDITOR_BUTTON:
					checkMapNameValid();
					break;
				case GUI_ID_READY:
					m_core->m_state = READY;
					if (m_core->_playerId == 0)
						m_core->m_menu.m_roomS->setVisible(false);
					else
						m_core->m_menu.m_roomC->setVisible(false);
					m_core->m_menu.m_ready->setVisible(true);
					break;
				case GUI_ID_UNREADY:
					m_core->m_state = UNREADY;
					m_core->m_menu.m_ready->setVisible(false);
					if (m_core->_playerId == 0)
						m_core->m_menu.m_roomS->setVisible(true);
					else
						m_core->m_menu.m_roomC->setVisible(true);
					break;
				case GUI_ID_PLAY_CLIENT:
					//m_core->m_state = CONNECT;
					m_core->m_menu.m_join->setVisible(true);
					m_core->m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_PLAY_SERVER:
					m_core->m_state = LAUNCH_SERVER;
					m_core->m_menu.m_roomS->setVisible(true);
					m_core->m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_JOIN_BACK_BUTTON:
					m_core->m_menu.m_join->setVisible(false);
					m_core->m_menu.m_play->setVisible(true);
					break;
				case GUI_ID_JOIN_BUTTON:
					m_core->m_state = CONNECT;
					m_core->m_menu.m_join->setVisible(false);
					m_core->m_menu.m_roomC->setVisible(true);
					break;
				case GUI_ID_MAP_SAVE_BUTTON:
					m_core->m_menu.m_mapEdit->setVisible(false);
					m_core->m_menu.m_mapMenu->setVisible(true);
					m_core->m_run = false;
					break;
				case GUI_ID_DOWN_BUTTON:
					m_core->m_menu.m_down->setVisible(false);
					m_core->m_menu.m_main->setVisible(true);
					m_core->m_state = MENU;
					break;
				case GUI_ID_LOCAL:
					m_core->m_menu.m_local->setVisible(true);
					m_core->m_menu.m_play->setVisible(false);
					break;
				case GUI_ID_LOCAL_BACK:
					m_core->m_menu.m_local->setVisible(false);
					m_core->m_menu.m_play->setVisible(true);
					break;
				case GUI_ID_LEAVE_GAME_BUTTON:
					m_core->exitGame();
					m_core->m_state = MENU;
					m_core->m_menu.m_gameOptions->setVisible(false);
					m_core->m_menu.m_main->setVisible(true);
					break;
				case GUI_ID_QUIT_GAME_BUTTON:
					m_core->m_run = false;
					break;
				case GUI_ID_STAY_GAME_BUTTON:
					m_core->m_menu.m_gameOptions->setVisible(false);
					m_core->m_core.getCamera().change(m_core->m_core.getSceneManager(), Camera::FPS);
					m_core->m_core.m_device->getCursorControl()->setVisible(false);
					break;
				case GUI_ID_NUMPAD_0:
				case GUI_ID_NUMPAD_1:
				case GUI_ID_NUMPAD_2:
				case GUI_ID_NUMPAD_3:
				case GUI_ID_NUMPAD_4:
				case GUI_ID_NUMPAD_5:
				case GUI_ID_NUMPAD_6:
				case GUI_ID_NUMPAD_7:
				case GUI_ID_NUMPAD_8:
				case GUI_ID_NUMPAD_9:
				case GUI_ID_NUMPAD_DOT:
				case GUI_ID_NUMPAD_DEL:
					updateIpInput(id);
					break;
				case GUI_ID_SOUND:
					{
						auto volume = engine->getSoundVolume();
						irr::gui::IGUIButton *btn = static_cast<irr::gui::IGUIButton *>(m_core->m_core.m_gui->getRootGUIElement()->getElementFromId(id, true));

						if (volume == 0) {
							engine->setSoundVolume(0.3);
							btn->setImage(m_core->m_core.m_driver->getTexture("assets/models/menu/volume.png"));
						}
						else {
							engine->setSoundVolume(0);
							btn->setImage(m_core->m_core.m_driver->getTexture("assets/models/menu/volume_mute.png"));
						}
					}
					break;
				default:
					sound = false;
					break;
			}
			if (sound)
				engine->play2D("music/select.wav", false, false, false);
		}
	}
}