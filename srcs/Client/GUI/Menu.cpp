/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Menu
*/

#include <memory>
#include "Menu.hpp"

Indie::Menu::Menu() :
	m_font(), m_sceneManager(), m_driver(), m_gui(), m_images()
{}

Indie::Menu::~Menu()
{}

void Indie::Menu::loadMenu(irr::IrrlichtDevice *device, const Options &opt)
{
	m_driver = device->getVideoDriver();
	m_sceneManager = device->getSceneManager();
	m_gui = device->getGUIEnvironment();
	m_images = m_driver->getTexture("assets/models/menu/menu.png");
 	irr::gui::IGUISkin* skin = m_gui->getSkin();

	m_root = m_gui->getRootGUIElement();

	m_main = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAIN_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_play = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_PLAY_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_option = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_OPTION_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_mapEdit = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAP_EDIT_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));

	m_root->addChild(m_mapEdit);
	m_root->addChild(m_option);
	m_root->addChild(m_play);
	m_root->addChild(m_main);

	m_main->setVisible(true);
	m_mapEdit->setVisible(false);
	m_option->setVisible(false);
	m_play->setVisible(false);

	if (!m_images)
		throw std::runtime_error("Error: can't load menu's images.");
	m_font = m_gui->getFont("assets/fonts/font.xml");
	if (!m_font)
		throw std::runtime_error("Error: can't load fonts");
	skin->setFont(m_font);

	loadMainMenu();
	loadOptionsMenu();
	loadMapMenu();
	loadPlayMenu();

	for (auto &btn : m_btns) {
		btn->setImage(m_driver->getTexture("assets/models/menu/button.png"));
		btn->setPressedImage(m_driver->getTexture("assets/models/menu/button_hover.png"));
	}
}

void Indie::Menu::loadMainMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500,250,800,250 + 50), m_main, GUI_ID_PLAY_BUTTON,
            L"Play", L"Launches the game"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500,325,800,325 + 50), m_main, GUI_ID_MAP_BUTTON,
            L"Map Editor", L"Create your own maps"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500,400,800,400 + 50), m_main, GUI_ID_OPTIONS_BUTTON,
            L"Option", L"Host or join a server"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500,475,800,475 + 50), m_main, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits the program"));
}

void Indie::Menu::loadOptionsMenu()
{
	// m_btns.emplace_back(m_gui->addButton(irr::core::recti(500, 250, 800, 250 + 50), m_option, GUI_ID_MAP_BUTTON,
		// L"TEST"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500, 325, 800, 325 + 50), m_option, GUI_ID_OPTION_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::loadMapMenu()
{
	// m_btns.emplace_back(m_gui->addButton(irr::core::recti(500, 250, 800, 250 + 50), m_mapEdit, GUI_ID_MAP_BUTTON,
		// L"TEST"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500, 325, 800, 325 + 50), m_mapEdit, GUI_ID_MAP_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::loadPlayMenu()
{
	// m_btns.emplace_back(m_gui->addButton(irr::core::recti(500, 250, 800, 250 + 50), m_play, GUI_ID_MAP_BUTTON,
		// L"TEST"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(500, 325, 800, 325 + 50), m_play, GUI_ID_PLAY_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::initSpriteMenu(std::vector<SpriteMenu> &sprites)
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

void Indie::Menu::setSkinTransparency(irr::s32 alpha , irr::gui::IGUISkin *skin)
{
	for (irr::s32 i=0; i<irr::gui::EGDC_COUNT ; ++i) {
		irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(alpha);
		skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
	}
}

Indie::MenuState Indie::Menu::display()
{
	//irr::gui::IGUIFont *font = m_gui->getFont("fontlucida.png");
	// irr::gui::IGUIStaticText *texte = m_gui->addStaticText(L"Apprendre Irrlicht les yeux fermés avec le\n"
    	// 							" 'Petit guide d'Irrlicht' de Kevin Leonhart",
    	// 			irr::core::rect<irr::s32>(100,20,400,100), true, true, 0, -1, true);

	// texte->setOverrideFont(m_font);

	m_gui->drawAll();

	// irr::video::SColor color(255, 255, 255, 255);
	// irr::core::position2di mouse = event.MouseState.Position;
	// irr::core::dimension2di imgSize = {285, 64};
	// std::array<SpriteMenu, 3> sprites;
	// int hovered;
	// initSpriteMenu(sprites);

	// for (auto &sprite : sprites) {
	// 	if (sprite.m_zone.isPointInside(mouse)) {
	// 		hovered = 0;
	// 		if (event.MouseState.LeftButtonDown)
	// 			return sprite.m_return;
	// 	}
	// 	else
	// 		hovered = 1;
	// 	m_driver->draw2DImage(m_images,
	// 		irr::core::position2di(sprite.m_zone.UpperLeftCorner),
	// 		sprite.m_images[hovered], 0, color, true);
	// }
	return NONE;
}