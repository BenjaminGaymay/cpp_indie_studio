/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Menu
*/

#include "Menu.hpp"

Indie::Menu::Menu()
{}

Indie::Menu::~Menu()
{}

void Indie::Menu::loadMenu(irr::IrrlichtDevice *device)
{
	m_driver = device->getVideoDriver();
	m_sceneManager = device->getSceneManager();
	m_gui = device->getGUIEnvironment();
	m_images = m_driver->getTexture("assets/models/menu/azerty.png");

	if (!m_images)
		throw std::runtime_error("Error: can't load menu's images.");
}

void Indie::Menu::initSpriteMenu(std::array<SpriteMenu, 3> &sprites)
{
	sprites[0].m_images = {
		{0, 0, 285, 64},
		{0, 64, 285, 128}
	};
	sprites[0].m_zone = {500, 75, 784, 139};
	sprites[0].m_return = PLAY;
	sprites[1].m_images = {
		{0, 128, 285, 192},
		{0, 192, 285, 256}
	};
	sprites[1].m_zone = {500, 150, 784, 214};
	sprites[2].m_return = QUIT;
		sprites[2].m_images = {
		{0, 256, 285, 323},
		{0, 323, 285, 384}
	};
	sprites[2].m_zone = {500, 225, 784, 289};
	sprites[2].m_return = GEN_MAP;
}

Indie::MenuState Indie::Menu::display(const Events &event)
{
	irr::video::SColor color(255, 255, 255, 255);
	irr::core::position2di mouse = event.MouseState.Position;
	irr::core::dimension2di imgSize = {285, 64};
	std::array<SpriteMenu, 3> sprites;
	int hovered;
	initSpriteMenu(sprites);

	for (auto &sprite : sprites) {
		if (sprite.m_zone.isPointInside(mouse)) {
			hovered = 0;
			if (event.MouseState.LeftButtonDown)
				return sprite.m_return;
		}
		else
			hovered = 1;
		m_driver->draw2DImage(m_images,
			irr::core::position2di(sprite.m_zone.UpperLeftCorner),
			sprite.m_images[hovered], 0, color, true);
	}
	return NONE;
}