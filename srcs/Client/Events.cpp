/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Events
*/

#include "Events.hpp"

Indie::Events::Events()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

bool Indie::Events::OnEvent(const irr::SEvent &event)
{
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