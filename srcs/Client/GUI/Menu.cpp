/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Menu
*/

#include <memory>
#include "Menu.hpp"

Indie::Menu::Menu()
{
	m_height = 95;
	m_width = 325;
}

Indie::Menu::~Menu()
{}

void Indie::Menu::loadMenu(irr::IrrlichtDevice *device, const Options &opt)
{
	m_opt = opt;
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
	m_room = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_ROOM_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));

	m_root->addChild(m_mapEdit);
	m_root->addChild(m_option);
	m_root->addChild(m_room);
	m_root->addChild(m_play);
	m_root->addChild(m_main);

	m_main->setVisible(true);
	m_mapEdit->setVisible(false);
	m_option->setVisible(false);
	m_play->setVisible(false);
	m_room->setVisible(false);

	if (!m_images)
		throw std::runtime_error("Error: can't load menu's images.");
	m_font = m_gui->getFont("assets/fonts/font.xml");
	if (!m_font)
		throw std::runtime_error("Error: can't load fonts");
	skin->setFont(m_font);

	loadMainMenu();
	loadOptionsMenu();
	loadMapMenu();
	loadRoomMenu();
	loadPlayMenu();

	for (auto &btn : m_btns) {
		btn->setImage(m_driver->getTexture("assets/models/menu/button.png"));
		btn->setPressedImage(m_driver->getTexture("assets/models/menu/button_hover.png"));
		btn->setUseAlphaChannel(true);
		btn->setDrawBorder(0);
	}
}

void Indie::Menu::loadMainMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left,200,x_right,200 + m_height), m_main, GUI_ID_PLAY_BUTTON,
            L"Play", L"Launches the game"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left,310,x_right,310 + m_height), m_main, GUI_ID_MAP_BUTTON,
            L"Map Editor", L"Create your own maps"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left,420,x_right,420 + m_height), m_main, GUI_ID_OPTIONS_BUTTON,
            L"Option", L"Changes options"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left,530,x_right,530 + m_height), m_main, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits the program"));
}

void Indie::Menu::loadOptionsMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 325, x_right, 325 + m_height), m_option, GUI_ID_OPTION_BACK_BUTTON,
		L"Back"));
	m_gui->addCheckBox(m_opt.getFullScreen(), irr::core::recti(m_width, m_height, m_width + 250, m_height + 50), m_option, GUI_ID_FULLSCREEN, L"FullScreen");
}

void Indie::Menu::loadMapMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 215, x_right, 215 + m_height), m_mapEdit, GUI_ID_MAP_EDITOR_BUTTON,
		L"Map Editor"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 325, x_right, 325 + m_height), m_mapEdit, GUI_ID_MAP_RANDOM_BUTTON,
		L"Random map"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 435, x_right, 435 + m_height), m_mapEdit, GUI_ID_MAP_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::loadPlayMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 215, x_right, 215 + m_height), m_play, GUI_ID_PLAY_SERVER, L"CREATE ROOM"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 325, x_right, 325 + m_height), m_play, GUI_ID_PLAY_CLIENT, L"JOIN ROOM"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 435, x_right, 435 + m_height), m_play, GUI_ID_PLAY_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::loadRoomMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 215, x_right, 215 + m_height), m_room, GUI_ID_READY, L"READY"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 325, x_right, 325 + m_height), m_room, GUI_ID_ROOM_BACK_BUTTON,
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
	sprites[1].m_return = QUIT;
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

Indie::AppState Indie::Menu::display()
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