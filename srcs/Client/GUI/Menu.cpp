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
	m_square_height = 100;
	m_square_width = 100;
}

Indie::Menu::~Menu()
{
	delete m_main;
	delete m_option;
	delete m_play;
	delete m_roomS;
	delete m_roomC;
	delete m_mapMenu;
	delete m_mapEdit;
	delete m_down;
	delete m_gameOptions;
	delete m_join;
	delete m_ready;
	delete m_local;
}

void Indie::Menu::loadMenu(irr::IrrlichtDevice *device, const Options &opt)
{
	m_opt = opt;
	m_driver = device->getVideoDriver();
	m_sceneManager = device->getSceneManager();
	m_gui = device->getGUIEnvironment();
	m_images = m_driver->getTexture("assets/models/menu/menu.png");
 	irr::gui::IGUISkin* skin = m_gui->getSkin();

	m_xLeft = (m_opt.getWidth() / 2) - (m_width / 2);
	m_xRight = (m_opt.getWidth() / 2) + (m_width / 2);

	m_root = m_gui->getRootGUIElement();

	m_main = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAIN_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_play = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_PLAY_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_option = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_OPTION_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_mapMenu = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAP_EDIT_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_mapEdit = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_MAP_EDIT_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_join = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_JOIN_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_roomS = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_ROOMS_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_roomC = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_ROOMC_MENU_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_down = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_DOWN_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_gameOptions = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_GAME_OPTIONS_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_ready = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_READY_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));
	m_local = new irr::gui::IGUIElement(irr::gui::EGUIET_TAB, m_gui, m_root, GUI_ID_READY_ELEMENT, irr::core::rect<irr::s32>(0, 0, opt.getWidth(), opt.getHeight()));

	m_main->setVisible(true);
	m_option->setVisible(false);
	m_play->setVisible(false);
	m_roomS->setVisible(false);
	m_roomC->setVisible(false);
	m_mapMenu->setVisible(false);
	m_mapEdit->setVisible(false);
	m_down->setVisible(false);
	m_gameOptions->setVisible(false);
	m_join->setVisible(false);
	m_ready->setVisible(false);
	m_local->setVisible(false);

	if (!m_images)
		throw std::runtime_error("Error: can't load menu's images.");
	m_font = m_gui->getFont("assets/fonts/font.xml");
	if (!m_font)
		throw std::runtime_error("Error: can't load fonts");
	skin->setFont(m_font);

	loadMainMenu();
	loadOptionsMenu();
	loadMapMenu();
	loadRoomSMenu();
	loadRoomCMenu();
	loadPlayMenu();
	loadDownMenu();
	loadGameOptionsMenu();
	loadJoinMenu();
	loadReadyMenu();
	loadSoundBtn();
	loadLocalGame();

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
	for (auto &btn : m_square_btns) {
		btn->setImage(m_driver->getTexture("assets/models/menu/square_button.png"));
		btn->setPressedImage(m_driver->getTexture("assets/models/menu/square_button_hover.png"));
		btn->setUseAlphaChannel(true);
		btn->setDrawBorder(0);
	}
}

void Indie::Menu::loadMainMenu()
{
	irr::video::ITexture *image = m_driver->getTexture ("assets/models/menu/background.png");

	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft,200,m_xRight,200 + m_height), m_main, GUI_ID_PLAY_BUTTON,
            L"Play", L"Launches the game"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft,310,m_xRight,310 + m_height), m_main, GUI_ID_MAP_BUTTON,
            L"Map Editor", L"Create your own maps"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft,420,m_xRight,420 + m_height), m_main, GUI_ID_OPTIONS_BUTTON,
            L"Option", L"Changes options"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft,530,m_xRight,530 + m_height), m_main, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits the program"));
	m_gui->addImage(image, irr::core::vector2di(0, 0), true, m_main);
}

void Indie::Menu::loadReadyMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_ready, GUI_ID_UNREADY, L"NOT READY"));
}

void Indie::Menu::loadOptionsMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_option, GUI_ID_OPTION_BACK_BUTTON,
		L"Back"));
	m_gui->addCheckBox(m_opt.getFullScreen(), irr::core::recti(m_width, m_height, m_width + 250, m_height + 50), m_option, GUI_ID_FULLSCREEN, L"FullScreen");
}

void Indie::Menu::loadJoinMenu()
{
	irr::gui::IGUIEditBox *edit = m_gui->addEditBox(L"127.0.0.1", irr::core::rect<irr::s32>(m_xLeft,90,m_xRight,90 + m_height - 10), true, m_join, GUI_ID_IP);
	edit->setMax(15);
	edit->setOverrideColor(irr::video::SColor(255, 0, 0, 255));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_join, GUI_ID_JOIN_BUTTON,
		L"Join"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_join, GUI_ID_JOIN_BACK_BUTTON,
		L"Back"));

	{
		int counter = 0;
		int x = 1;
		int y = 2;
		int id = GUI_ID_NUMPAD_0;
		for (; counter <= 11; counter++) {
			if (counter != 0 && counter % 3 == 0) {
				y++;
				x = 1;
			}
			m_square_btns.emplace_back(m_gui->addButton(irr::core::recti(x * 100, y * 100, (x+1) * 100, (y+1) * 100),
						m_join, id, std::to_wstring(counter).c_str()));
			std::cout << id << std::endl;
			id++;
			x++;
		}
		m_square_btns[9]->setText(L".");
		m_square_btns[10]->setText(L"9");
		m_square_btns[11]->setText(L"DEL");
	}
}

void Indie::Menu::loadDownMenu()
{
	m_gui->addStaticText(L"Server is down", irr::core::rect<irr::s32>(m_xLeft + 20, 250, m_xRight + 50, 250 + m_height), false, true, m_down);
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 435, m_xRight, 435 + m_height), m_down, GUI_ID_DOWN_BUTTON, L"Back to menu"));
}

void Indie::Menu::loadMapMenu()
{
	irr::gui::IGUIEditBox *edit = m_gui->addEditBox(L"Map's name", irr::core::rect<irr::s32>(m_xLeft,90,m_xRight,90 + m_height - 10), true, m_mapMenu, GUI_ID_MAP_NAME);
	edit->setMax(10);
	edit->setOverrideColor(irr::video::SColor(255, 0, 0, 255));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_mapMenu, GUI_ID_MAP_EDITOR_BUTTON,
		L"Map Editor"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_mapMenu, GUI_ID_MAP_RANDOM_BUTTON,
		L"Random map"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 435, m_xRight, 435 + m_height), m_mapMenu, GUI_ID_MAP_BACK_BUTTON,
		L"Back"));
	// m_gui->addStaticText(L"S to save", irr::core::recti(10, 10, 10 + m_width, 10 + m_height), true, true, m_mapEdit);
	m_small_btns.emplace_back(m_gui->addButton(irr::core::recti(10, m_opt.getHeight() / 2 - m_small_height / 2 , m_small_width, m_opt.getHeight() / 2 + m_small_height / 2 ), m_mapEdit, GUI_ID_MAP_SAVE_BUTTON,
		L"Save"));
}

void Indie::Menu::loadPlayMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 105, m_xRight, 105 + m_height), m_play, GUI_ID_LOCAL, L"LOCAL"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_play, GUI_ID_PLAY_SERVER, L"CREATE ROOM"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_play, GUI_ID_PLAY_CLIENT, L"JOIN ROOM"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 435, m_xRight, 435 + m_height), m_play, GUI_ID_PLAY_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::chooseMap(irr::s32 id)
{
	DIR* dirp = opendir("./assets/maps/");
    	struct dirent *dp;

	m_map.clear();
    	while ((dp = readdir(dirp)) != NULL)
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
			m_map.push_back(dp->d_name);
    	closedir(dirp);
	irr::gui::IGUIListBox *list = static_cast<irr::gui::IGUIListBox*>(m_gui->getRootGUIElement()->getElementFromId(id, true));
	list->clear();
	for (auto &c : m_map)
		list->addItem(irr::core::stringw(c.c_str()).c_str());
	list->setSelected(0);
}

void Indie::Menu::loadRoomSMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_roomS, GUI_ID_READY, L"READY"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_roomS, GUI_ID_ROOM_BACK_BUTTON,
		L"Back"));

	m_gui->addStaticText(L"Select your map:", irr::core::recti(100, 20, 800, 20 + m_height), false, true, m_roomS)->setOverrideColor(irr::video::SColor(150, 255, 0, 255));
	irr::gui::IGUIListBox *list = m_gui->addListBox(irr::core::recti(100, 100, 400, m_opt.getHeight() - 100), m_roomS, GUI_ID_LIST_MAP);
	chooseMap(GUI_ID_LIST_MAP);
}

void Indie::Menu::loadRoomCMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_roomC, GUI_ID_READY, L"READY"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_roomC, GUI_ID_ROOM_BACK_BUTTON,
		L"Back"));
}

void Indie::Menu::loadGameOptionsMenu()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_gameOptions, GUI_ID_STAY_GAME_BUTTON, L"CONTINUE"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_gameOptions, GUI_ID_LEAVE_GAME_BUTTON, L"LEAVE ROOM"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 435, m_xRight, 435 + m_height), m_gameOptions, GUI_ID_QUIT_GAME_BUTTON, L"QUIT GAME"));

}

void Indie::Menu::setSkinTransparency(irr::s32 alpha , irr::gui::IGUISkin *skin)
{
	for (irr::s32 i=0; i<irr::gui::EGDC_COUNT ; ++i) {
		irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(alpha);
		skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
	}
}

void Indie::Menu::loadSoundBtn()
{
	irr::gui::IGUIButton *btn = m_gui->addButton(irr::core::recti(10, m_opt.getHeight() - 85, 85, m_opt.getHeight() - 10), m_root, GUI_ID_SOUND, L"", L"Mute/Unmute");

	btn->setImage(m_driver->getTexture("assets/models/menu/volume.png"));
	btn->setUseAlphaChannel(true);
	btn->setDrawBorder(0);
}

void Indie::Menu::loadLocalGame()
{
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 215, m_xRight, 215 + m_height), m_local, GUI_ID_READY, L"Play"));
	m_btns.emplace_back(m_gui->addButton(irr::core::recti(m_xLeft, 325, m_xRight, 325 + m_height), m_local, GUI_ID_LOCAL_BACK, L"Back"));
	irr::gui::IGUIListBox *list = m_gui->addListBox(irr::core::recti(100, 100, 400, m_opt.getHeight() - 100), m_local, GUI_ID_LIST_MAP);

	for (auto &c : m_map)
		list->addItem(irr::core::stringw(c.c_str()).c_str());
	list->setSelected(0);
}

Indie::AppState Indie::Menu::display()
{
	m_gui->drawAll();
	return NONE;
}