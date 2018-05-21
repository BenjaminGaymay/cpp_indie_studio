/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Events
*/
#include <iostream>

#include "Events.hpp"

Indie::Events::Events() :
	MouseState(), Context()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

void Indie::Events::load(AppContext &context)
{
	Context = context;
}

bool Indie::Events::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_GUI_EVENT) {
		irr::s32 id = event.GUIEvent.Caller->getID();
		irr::gui::IGUIEnvironment *env = Context.device->getGUIEnvironment();

		switch (event.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED:
                		switch(id) {
                			case GUI_ID_QUIT_BUTTON:
                    				Context.device->closeDevice();
                    				break;
					case GUI_ID_PLAY_BUTTON:
						Context.menu->m_main->setVisible(false);
						Context.menu->m_play->setVisible(true);
                    				break;
					case GUI_ID_OPTIONS_BUTTON:
						Context.menu->m_option->setVisible(true);
						Context.menu->m_main->setVisible(false);
						break;
					case GUI_ID_SERVER_BUTTON:
						std::cout << "launch server" << std::endl;
						break;
					case GUI_ID_MAP_BUTTON:
						Context.menu->m_mapEdit->setVisible(true);
						Context.menu->m_main->setVisible(false);
						break;
					case GUI_ID_OPTION_BACK_BUTTON:
						Context.menu->m_main->setVisible(true);
						Context.menu->m_option->setVisible(false);
						break;
					case GUI_ID_PLAY_BACK_BUTTON:
						Context.menu->m_main->setVisible(true);
						Context.menu->m_play->setVisible(false);
						break;
					case GUI_ID_MAP_BACK_BUTTON:
						Context.menu->m_main->setVisible(true);
						Context.menu->m_mapEdit->setVisible(false);
						break;
					case GUI_ID_FULLSCREEN:
						// if (!Context.options->getFullScreen()) {
						// 	Context.options->setFullScreen(true);
						// 	irr::core::dimension2d<irr::u32> dimension(Context.options->getWidth(), Context.options->getHeight());
						// 	Context.device->drop();
						// 	Context.device = irr::createDevice(irr::video::EDT_OPENGL,
						// 		dimension, 32, Context.options->getFullScreen(), true, false, this);
						// }
						break;
					case GUI_ID_PLAY:
						break;
					default:
						break;
			}
			case irr::gui::EGET_FILE_SELECTED:
			{
			// show the model filename, selected in the file dialog
			// irr::gui::IGUIFileOpenDialog* dialog =
			// 	(irr::gui::IGUIFileOpenDialog*)event.GUIEvent.Caller;
			// if (dialog->getFileName())
			// 	std::cout << dialog->getFileName() << std::endl;
			// Context.listbox->addItem(dialog->getFileName());
			}
                break;
			default:
				break;
		}
	}

	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;
			case irr::EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;
			case irr::EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;
			default:
				break;
		}
	}
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
}

bool Indie::Events::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

Indie::SMouseState::SMouseState() :
	LeftButtonDown(false)
{}