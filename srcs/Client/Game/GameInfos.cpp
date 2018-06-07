//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// GameInfos
//

#include "Core.hpp"

void Indie::Core::comGameInfos(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	switch (event) {
		case START:
			_state = PLAYING;
			m_state = PLAY;
			m_menu.m_ready->setVisible(false);
			m_core.m_device->getCursorControl()->setVisible(false);
			m_core.getCamera().change(m_core.getSceneManager(), Camera::FPS);
			break;
		case MESSAGE: serverMessage(infos); break;
		case EV_READY: {
			const auto &id = std::stoi(infos[0]);
			_readyPlayers[id] = EV_READY;
			break;
		}
		case EV_UNREADY : {
			const auto &id = std::stoi(infos[0]);
			_readyPlayers[id] = EV_UNREADY;
			break;
		}
		case INFO: saveLocalGame(infos); break;
		default: break;
	}
}
