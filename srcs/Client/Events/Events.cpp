//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Events
//

#include <ik_ISound.h>
#include "Events.hpp"

Indie::Events::Events() :
	MouseState(), ButtonClicked{false}, KeyIsDown{false}
{}

bool Indie::Events::isButtonClicked(IdGui id)
{
	bool state;

	if (id >= 0 && id < BTN_COUNT) {
		state = ButtonClicked[id];
		ButtonClicked[id] = false;
		return state;
	}
	return false;
}

bool Indie::Events::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_GUI_EVENT) {
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
			irr::s32 id = event.GUIEvent.Caller->getID();
			id -= 101;
			if (id >= 0 && id < BTN_COUNT)
				ButtonClicked[id] = true;
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

	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
        return false;
}

bool Indie::Events::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

Indie::SMouseState::SMouseState() :
	LeftButtonDown(false)
{}
