//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Menu
//

#include "Menu.hpp"

Indie::Menu::Menu()
{
	m_height = 95;
	m_width = 325;
	m_small_height = 72;
	m_small_width = 250;
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
	m_mapMenu = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAP_EDIT_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_mapEdit = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAP_EDIT_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_room = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_ROOM_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_down = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_DOWN_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));

	m_main->setVisible(true);
	m_option->setVisible(false);
	m_play->setVisible(false);
	m_room->setVisible(false);
	m_mapMenu->setVisible(false);
	m_mapEdit->setVisible(false);
	m_down->setVisible(false);

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
	loadDownMenu();

	// m_btns.emplace_back(m_gui->addButton(irr::core::recti(500,200,800,200 + m_height), m_root, GUI_ID_PLAY_BUTTON,
        //     L"Play", L"Launches the game"));
	for (auto &btn : m_btns) {
		btn->setImage(m_driver->getTexture("assets/models/menu/button.png"));
		btn->setPressedImage(m_driver->getTexture("assets/models/menu/button_hover.png"));
		btn->setUseAlphaChannel(true);
		btn->setDrawBorder(0);
	}
	for (auto &btn : m_small_btns) {
		btn->setImage(m_driver->getTexture("assets/models/menu/small_button.png"));
		btn->setPressedImage(m_driver->getTexture("assets/models/menu/small_button_hover.png"));
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

void Indie::Menu::loadDownMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_gui->addStaticText(L"Server is down", irr::core::rect<irr::s32>(x_left + 20, 250, x_right + 50, 250 + m_height), false, true, m_down);
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 435, x_right, 435 + m_height), m_down, GUI_ID_DOWN_BUTTON, L"Back to menu"));
}

void Indie::Menu::loadMapMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	irr::gui::IGUIEditBox *edit = m_gui->addEditBox(L"Map's name", irr::core::rect<irr::s32>(x_left,90,x_right,90 + m_height - 10), true, m_mapMenu, GUI_ID_MAP_NAME);
	edit->setMax(10);
	edit->setOverrideColor(irr::video::SColor(255, 0, 0, 255));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 215, x_right, 215 + m_height), m_mapMenu, GUI_ID_MAP_EDITOR_BUTTON,
		L"Map Editor"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 325, x_right, 325 + m_height), m_mapMenu, GUI_ID_MAP_RANDOM_BUTTON,
		L"Random map"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 435, x_right, 435 + m_height), m_mapMenu, GUI_ID_MAP_BACK_BUTTON,
		L"Back"));
	// m_gui->addStaticText(L"S to save", irr::core::recti(10, 10, 10 + m_width, 10 + m_height), true, true, m_mapEdit);
	m_small_btns.emplace_back(m_gui->addButton(irr::core::recti(10, m_opt.getHeight() / 2 - m_small_height / 2 , m_small_width, m_opt.getHeight() / 2 + m_small_height / 2 ), m_mapEdit, GUI_ID_MAP_SAVE_BUTTON,
		L"Save"));
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

void Indie::Menu::chooseMap()
{
	DIR* dirp = opendir("./assets/maps/");
    	struct dirent * dp;
    	while ((dp = readdir(dirp)) != NULL) {
		    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			    v_map.push_back(dp->d_name);
			    std::cout << dp->d_name << std::endl;
		    }
    	}
    	closedir(dirp);
}


void Indie::Menu::loadRoomMenu()
{
	std::size_t x_left = (m_opt.getWidth() / 2) - (m_width / 2);
	std::size_t x_right = (m_opt.getWidth() / 2) + (m_width / 2);

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 215, x_right, 215 + m_height), m_room, GUI_ID_READY, L"READY"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(x_left, 325, x_right, 325 + m_height), m_room, GUI_ID_ROOM_BACK_BUTTON,
		L"Back"));

	chooseMap();
	std::cout << v_map.size() << std::endl;
	m_gui->addStaticText(L"Select your map:", irr::core::recti(100, 20, 800, 20 + m_height), false, true, m_room)->setOverrideColor(irr::video::SColor(150, 255, 0, 255));
	irr::gui::IGUIListBox *list = m_gui->addListBox(irr::core::recti(100, 100, 400, m_opt.getHeight() - 100), m_room, ID_GUI_LIST_MAP);
	for (auto &c : v_map)
		list->addItem(irr::core::stringw(c.c_str()).c_str());
	list->setSelected(0);
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
	m_gui->drawAll();
	return NONE;
}