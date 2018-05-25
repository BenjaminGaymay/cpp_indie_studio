//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Events
//

#include "Events.hpp"

Indie::Events::Events() :
	MouseState(), ButtonClicked{
		{GUI_ID_QUIT_BUTTON, false},
		{GUI_ID_PLAY_BUTTON, false},
		{GUI_ID_OPTIONS_BUTTON, false},
		{GUI_ID_SERVER_BUTTON, false},
		{GUI_ID_MAP_BUTTON, false},
		{GUI_ID_PLAY_MENU_ELEMENT, false},
		{GUI_ID_OPTION_MENU_ELEMENT, false},
		{GUI_ID_MAP_EDIT_MENU_ELEMENT, false},
		{GUI_ID_MAIN_MENU_ELEMENT, false},
		{GUI_ID_ROOM_MENU_ELEMENT, false},
		{GUI_ID_ROOM_BACK_BUTTON, false},
		{GUI_ID_OPTION_BACK_BUTTON, false},
		{GUI_ID_PLAY_BACK_BUTTON, false},
		{GUI_ID_MAP_BACK_BUTTON, false},
		{GUI_ID_FULLSCREEN, false},
		{GUI_ID_PLAY_SERVER, false},
		{GUI_ID_PLAY_CLIENT, false},
		{GUI_ID_READY, false},
		{GUI_ID_MAP_EDITOR_BUTTON, false},
		{GUI_ID_MAP_RANDOM_BUTTON, false}
	}
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

bool Indie::Events::isButtonClicked(IdGui id)
{
	bool state;

	if (ButtonClicked.find(id) != ButtonClicked.end()) {
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
			if (ButtonClicked.find(static_cast<IdGui>(id)) != ButtonClicked.end()) {
				ButtonClicked[static_cast<IdGui>(id)] = true;
			}
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
