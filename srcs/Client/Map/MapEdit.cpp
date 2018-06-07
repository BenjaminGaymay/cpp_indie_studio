//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// MapEdit
//

#include <random>
#include "Core.hpp"
#include "ManageStrings.hpp"

int Indie::Core::createRandMap(std::string name, std::size_t x, std::size_t y)
{
	std::string file = "assets/maps/" + name;
	std::vector<std::vector<int>> map;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,1);

	if (x < 10 || y < 10 || x > 25 || y > 25) {
		std::cerr << "x and y minimum values are 10" << std::endl;
		return -1;
	}
	for (std::size_t i = 0; i < y; ++i) {
		std::vector<int> line;
		for (std::size_t j = 0; j < x; ++j) {
			int rand = distribution(generator);
			if (i % 2 == 0 && j % 3 == 0)
				line.push_back(8);
			else
				line.push_back(rand);
		}
		map.push_back(line);
	}

	for (std::size_t i = 0; i < x; ++i) {
		map[0][i] = 8;
		map[y - 1][i] = 8;
		map[i][0] = 8;
		map[i][x - 1] = 8;
	}

	// for (std::size_t i = 0; i < y; ++i) {
	// 	map[i][0] = 1;
	// 	map[i][x - 1] = 1;
	// }

	// TOP LEFT CORNER
	map[1][1] = 10;
	map[1][2] = 0;
	map[2][1] = 0;

	// TOP RIGHT CORNER
	map[1][x - 2] = 10;
	map[1][x - 3] = 0;
	map[2][x - 2] = 0;

	// BOT LEFT CORNER
	map[y - 2][1] = 10;
	map[y - 2][2] = 0;
	map[y - 3][1] = 0;

	// BOT RIGHT CORNER
	map[y - 2][x - 2] = 10;
	map[y - 2][x - 3] = 0;
	map[y - 3][x - 2] = 0;

	writeInFile(file, map);
	return 0;
}

void Indie::Core::createZeroMap(std::string name, size_t x, size_t y)
{
	std::string file = "assets/maps/" + name;
	std::vector<std::vector<int>> map;

	std::vector<int> first_line;
	for (std::size_t j = 0; j < x; ++j) {
		first_line.push_back(8);
	}
	map.push_back(first_line);
	for (std::size_t i = 1; i < y - 1; ++i) {
		std::vector<int> line;
		line.push_back(8);
		for (std::size_t j = 1; j < x - 1; ++j) {
			line.push_back(0);
		}
		line.push_back(8);
		map.push_back(line);
	}
	std::vector<int> end_line;
	for (std::size_t j = 0; j < x; ++j) {
		end_line.push_back(8);
	}
	map.push_back(end_line);
	writeInFile(file, map);
}

void Indie::Core::writeInFile(std::string file, std::vector<std::vector<int>> map)
{
	std::ofstream outfile (file);

	for (std::size_t i = 0; i < map.size(); ++i) {
		for (std::size_t j = 0; j < map[i].size(); ++j) {
			if (map[i][j] >= 0 && map[i][j] <= 9)
				outfile << "0";
			outfile << map[i][j] << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}

void Indie::Core::eraseTopandBot()
{
	auto &mapper = _game->getMapperEdit();
	
	bool a = (std::find(std::begin(mapper->getMap2d()[0]), std::end(mapper->getMap2d()[0]), 1) != std::end(mapper->getMap2d()[0]));
	while (a == 0) {
		mapper->getMap2d().erase(mapper->getMap2d().begin());
		a = (std::find(std::begin(mapper->getMap2d()[0]), std::end(mapper->getMap2d()[0]), 1) != std::end(mapper->getMap2d()[0]));
	}
	int i = mapper->getMap2d().size() - 1;
	a = (std::find(std::begin(mapper->getMap2d()[i]), std::end(mapper->getMap2d()[i]), 1) != std::end(mapper->getMap2d()[i]));
	while (a == 0) {
		mapper->getMap2d().erase(mapper->getMap2d().end());
		a = std::find(std::begin(mapper->getMap2d()[i]), std::end(mapper->getMap2d()[i]), 1) != std::end(mapper->getMap2d()[i]);
		--i;
	}
}

void Indie::Core::eraseLeftandRight()
{
	auto &mapper = _game->getMapperEdit();
	
	std::size_t min = mapper->getMap2d()[0].size();
	std::size_t max = 0;

	for (std::size_t i = 0; i < mapper->getMap2d().size(); ++i) {
		// calc min lenght
		for (std::size_t j = 0; j < mapper->getMap2d()[i].size(); ++j) {
			if (mapper->getMap2d()[i][j] == 1 && min > j) {
				min = j;
				break;
			}
		}
		// calc max lenght
		for (std::size_t j = mapper->getMap2d()[i].size() - 1; j > 0; --j) {
			if (mapper->getMap2d()[i][j] == 1 && max < j) {
				max = j + 1;
				break;
			}
		}
	}
	if (min == 25 || max == 25)
		return ;
	for (std::size_t i = 0; i < mapper->getMap2d().size(); ++i) {
		mapper->getMap2d()[i].erase(mapper->getMap2d()[i].begin() + max, mapper->getMap2d()[i].end());
		mapper->getMap2d()[i].erase(mapper->getMap2d()[i].begin(), mapper->getMap2d()[i].begin() + min);
	}
}

void Indie::Core::cleanMap()
{
	auto &mapper = _game->getMapperEdit();
	
	int is_empty = 0;
	for (std::size_t i = 0; i < mapper->getMap2d().size(); ++i) {
		for (std::size_t j = 0; j < mapper->getMap2d()[i].size(); ++j)
			if (mapper->getMap2d()[i][j] != 0)
				is_empty += 1;
		if (is_empty > 0)
			break;
	}
	if (is_empty == 0)
		return ;
	eraseTopandBot();
	eraseLeftandRight();
}

void Indie::Core::changeMapWithEvent(std::size_t x, std::size_t y)
{
	auto &mapper = _game->getMapperEdit();

	//BLOCKS
	if (_editState == BLOCK && _counter.first > 0 && mapper->getMap2d()[y][x] != 10 && mapper->getMap2d()[y][x] != 8) {
		(_editState == BLOCK ? (_counter.first -= (_counter.first == 0 ? 0 : 1)) : (_counter.second -= (_counter.second == 0 ? 0 : 1)));
		_counter.first += (mapper->getMap2d()[y][x] == 1 ? 2 : 0);
		mapper->getMap2d()[y][x] = (mapper->getMap2d()[y][x] == 1 ? 0 : 1);
	}
	//INDESTRUCTIBLE_BLOCK
	else if (_editState == INDESTRUCTIBLE_BLOCK && _counter.first > 0 && mapper->getMap2d()[y][x] != 10 && mapper->getMap2d()[y][x] != 1) {
		(_editState == INDESTRUCTIBLE_BLOCK ? (_counter.first -= (_counter.first == 0 ? 0 : 1)) : (_counter.second -= (_counter.second == 0 ? 0 : 1)));
		_counter.first += (mapper->getMap2d()[y][x] == 8 ? 2 : 0);
		mapper->getMap2d()[y][x] = (mapper->getMap2d()[y][x] == 8 ? 0 : 8);
	}
	//PERSO
	else if (_editState == PERSO && _counter.second > 0 && mapper->getMap2d()[y][x] != 1) {
		(_editState == BLOCK ? (_counter.first -= (_counter.first == 0 ? 0 : 1)) : (_counter.second -= (_counter.second == 0 ? 0 : 1)));
		_counter.second += (mapper->getMap2d()[y][x] == 10 ? 2 : 0);
		mapper->getMap2d()[y][x] = (mapper->getMap2d()[y][x] == 10 ? 0 : 10);
	}
	//SUPPR PERSO
	else if (_editState == PERSO && _counter.second == 0 && mapper->getMap2d()[y][x] == 10) {
		_counter.second += 1;
		mapper->getMap2d()[y][x] = 0;
	}
	_game->clear3dMap();
	mapper->load(_graphism);

}

int Indie::Core::editMapEvents()
{
	auto &mapper = _game->getMapperEdit();
	
	if (m_event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (_counter.second < 4 && m_run == false) {
		auto textbox = m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_MAP_NAME, true);
		auto mapName = ManageStrings::convertWchart(textbox->getText());
		writeInFile(std::string("assets/maps/" + mapName), mapper->getMap2d());
		return -1;
	} else if (m_event.MouseState.LeftButtonDown) {
		auto x = int((m_event.MouseState.Position.X - 435) / BLOCK_SIZE);
		auto y = int((m_event.MouseState.Position.Y - 15) / BLOCK_SIZE);
		if (x >= 1 && y >= 1 && x < 24 && y < 24)
			changeMapWithEvent(x, y);
		else if (x < 0 && y <= 2)
			_editState = BLOCK;
		else if (x < 0 && y <= 6)
			_editState = INDESTRUCTIBLE_BLOCK;
		else if (x < 0 && y <= 12)
			_editState = PERSO;
	}
	return 0;
}

void Indie::Core::editMap()
{
	auto textbox = m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_MAP_NAME, true);
	auto mapName = ManageStrings::convertWchart(textbox->getText());

	m_core.editMapView();
	createZeroMap(mapName, 25, 25);
	std::unique_ptr<Map> map(std::make_unique<Map>());
	_game->setMapper(std::move(map));
	auto &mapper = _game->getMapperEdit();
	mapper->newMap("assets/maps/" + mapName, 20.0f, 100.0f, _graphism);

	//SELECTION SIDE
	_editState = BLOCK;
	_counter = {529, 4};
	auto block =_graphism->createTexture(*_graphism->getTexture(1), {95, 300, 270}, {0, 0, 0}, {3, 3, 3}, false);
	_graphism->resizeNode(block, mapper->getSize());
	auto block2 =_graphism->createTexture(*_graphism->getTexture(8), {65, 300, 270}, {0, 0, 0}, {3, 3, 3}, false);
	_graphism->resizeNode(block2, mapper->getSize());
	auto perso =_graphism->createTexture(*_graphism->getTexture(10), {35, 300, 270}, {0, 0, 0}, {3, 3, 3}, false);
	_graphism->resizeNode(perso, mapper->getSize());
	while (m_core.m_device->run() && m_run) {
		processEvents();
		if (editMapEvents() == -1) {
			_game->clear3dMap();
			break;
		}
		m_core.m_driver->beginScene(true, true, _color);
		m_core.m_gui->drawAll();
    		m_core.m_sceneManager->drawAll();
		m_core.m_font->draw(irr::core::stringw(std::to_string(_counter.first).c_str()), irr::core::rect<irr::s32>(125, 25, 0, 0), irr::video::SColor(255,255,255,255));
		m_core.m_font->draw(irr::core::stringw(std::to_string(_counter.first).c_str()), irr::core::rect<irr::s32>(125, 125, 0, 0), irr::video::SColor(255,255,255,255));
		m_core.m_font->draw(irr::core::stringw(std::to_string(_counter.second).c_str()), irr::core::rect<irr::s32>(125, 225, 0, 0), irr::video::SColor(255,255,255,255));
		if (_editState == BLOCK)
			m_core.m_font->draw(irr::core::stringw("->"), irr::core::rect<irr::s32>(0, 25, 0, 0), irr::video::SColor(255,255,0,255));
		else if (_editState == INDESTRUCTIBLE_BLOCK)
			m_core.m_font->draw(irr::core::stringw("->"), irr::core::rect<irr::s32>(0, 125, 0, 0), irr::video::SColor(255,255,0,255));
		else
			m_core.m_font->draw(irr::core::stringw("->"), irr::core::rect<irr::s32>(0, 225, 0, 0), irr::video::SColor(255,255,0,255));
		m_core.m_driver->endScene();
	}
	m_run = true;
	_game->clear3dMap();
	_game->clear2dMap();
	block2->remove();
	block->remove();
	perso->remove();
}