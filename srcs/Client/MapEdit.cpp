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
			line.push_back(distribution(generator));
		}
		map.push_back(line);
	}

	for (std::size_t i = 0; i < x; ++i) {
		map[0][i] = 1;
		map[y - 1][i] = 1;
	}

	for (std::size_t i = 0; i < y; ++i) {
		map[i][0] = 1;
		map[i][x - 1] = 1;
	}

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

	for (std::size_t i = 0; i < y; ++i) {
		std::vector<int> line;
		for (std::size_t j = 0; j < x; ++j) {
			line.push_back(0);
		}
		map.push_back(line);
	}
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
	bool a = (std::find(std::begin(_mapper->getMap2d()[0]), std::end(_mapper->getMap2d()[0]), 1) != std::end(_mapper->getMap2d()[0]));
	while (a == 0) {
		_mapper->getMap2d().erase(_mapper->getMap2d().begin());
		a = (std::find(std::begin(_mapper->getMap2d()[0]), std::end(_mapper->getMap2d()[0]), 1) != std::end(_mapper->getMap2d()[0]));
	}
	int i = _mapper->getMap2d().size() - 1;
	a = (std::find(std::begin(_mapper->getMap2d()[i]), std::end(_mapper->getMap2d()[i]), 1) != std::end(_mapper->getMap2d()[i]));
	while (a == 0) {
		_mapper->getMap2d().erase(_mapper->getMap2d().end());
		a = std::find(std::begin(_mapper->getMap2d()[i]), std::end(_mapper->getMap2d()[i]), 1) != std::end(_mapper->getMap2d()[i]);
		--i;
	}
}

void Indie::Core::eraseLeftandRight()
{
	std::size_t min = _mapper->getMap2d()[0].size();
	std::size_t max = 0;

	for (std::size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		// calc min lenght
		for (std::size_t j = 0; j < _mapper->getMap2d()[i].size(); ++j) {
			if (_mapper->getMap2d()[i][j] == 1 && min > j) {
				min = j;
				break;
			}
		}
		// calc max lenght
		for (std::size_t j = _mapper->getMap2d()[i].size() - 1; j > 0; --j) {
			if (_mapper->getMap2d()[i][j] == 1 && max < j) {
				max = j + 1;
				break;
			}
		}
	}
	if (min == 25 || max == 25)
		return ;
	for (std::size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		_mapper->getMap2d()[i].erase(_mapper->getMap2d()[i].begin() + max, _mapper->getMap2d()[i].end());
		_mapper->getMap2d()[i].erase(_mapper->getMap2d()[i].begin(), _mapper->getMap2d()[i].begin() + min);
	}
}

void Indie::Core::cleanMap()
{
	int is_empty = 0;
	for (std::size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		for (std::size_t j = 0; j < _mapper->getMap2d()[i].size(); ++j)
			if (_mapper->getMap2d()[i][j] != 0)
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
	//BLOCKS
	if (_editState == BLOCK && _counter.first > 0 && _mapper->getMap2d()[y][x] != 10) {
		(_editState == BLOCK ? (_counter.first -= (_counter.first == 0 ? 0 : 1)) : (_counter.second -= (_counter.second == 0 ? 0 : 1)));
		_counter.first += (_mapper->getMap2d()[y][x] == 1 ? 2 : 0);
		_mapper->getMap2d()[y][x] = (_mapper->getMap2d()[y][x] == 1 ? 0 : 1);
	}
	//PERSO
	else if (_editState == PERSO && _counter.second > 0 && _mapper->getMap2d()[y][x] != 1) {
		(_editState == BLOCK ? (_counter.first -= (_counter.first == 0 ? 0 : 1)) : (_counter.second -= (_counter.second == 0 ? 0 : 1)));
		_counter.second += (_mapper->getMap2d()[y][x] == 10 ? 2 : 0);
		_mapper->getMap2d()[y][x] = (_mapper->getMap2d()[y][x] == 10 ? 0 : 10);
	}
	//SUPPR PERSO
	else if (_editState == PERSO && _counter.second == 0 && _mapper->getMap2d()[y][x] == 10) {
		_counter.second += 1;
		_mapper->getMap2d()[y][x] = 0;
	}
	_mapper->clear3dMap();
	_mapper->load(_graphism);

}

int Indie::Core::editMapEvents()
{
	if (m_event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (_counter.second < 4 && m_run == false) {
		auto textbox = m_core.m_gui->getRootGUIElement()->getElementFromId(GUI_ID_MAP_NAME, true);
		auto mapName = ManageStrings::convertWchart(textbox->getText());
		writeInFile(std::string("assets/maps/" + mapName), _mapper->getMap2d());
		return -1;
	} else if (m_event.MouseState.LeftButtonDown) {
		auto x = int((m_event.MouseState.Position.X - 435) / BLOCK_SIZE);
		auto y = int((m_event.MouseState.Position.Y - 15) / BLOCK_SIZE);
		if (x >= 0 && y >= 0 && x < 25 && y < 25)
			changeMapWithEvent(x, y);
		else if (x < 0 && y <= 2)
			_editState = BLOCK;
		else if (x < 0 && y <= 5)
			_editState = PERSO;
	}
	return 0;
}

void Indie::Core::editMap()
{
	m_core.editMapView();
	createZeroMap("mdr.txt", 25, 25);
	_mapper = std::make_unique<Map>();
	_mapper->newMap("assets/maps/mdr.txt", 20.0f, 100.0f, _graphism);

	//SELECTION SIDE
	_editState = BLOCK;
	_counter = {625, 4};
	auto block =_graphism->createTexture(*_graphism->getTexture(1), {95, 300, 270}, {0, 0, 0}, {3, 3, 3}, false);
	_graphism->resizeNode(block, _mapper->getSize());
	auto perso =_graphism->createTexture(*_graphism->getTexture(10), {70, 300, 270}, {0, 0, 0}, {3, 3, 3}, false);
	_graphism->resizeNode(perso, _mapper->getSize());

	while (m_core.m_device->run() && m_run) {
		processEvents();
		if (editMapEvents() == -1)
			break;
		m_core.m_driver->beginScene(true, true, _color);
		m_core.m_gui->drawAll();
    		m_core.m_sceneManager->drawAll();
		m_core.m_font->draw(irr::core::stringw(std::to_string(_counter.first).c_str()), irr::core::rect<irr::s32>(125, 25, 0, 0), irr::video::SColor(255,255,255,255));
		m_core.m_font->draw(irr::core::stringw(std::to_string(_counter.second).c_str()), irr::core::rect<irr::s32>(125, 105, 0, 0), irr::video::SColor(255,255,255,255));
		if (_editState == BLOCK)
			m_core.m_font->draw(irr::core::stringw("->"), irr::core::rect<irr::s32>(0, 25, 0, 0), irr::video::SColor(255,255,0,255));
		else
			m_core.m_font->draw(irr::core::stringw("->"), irr::core::rect<irr::s32>(0, 105, 0, 0), irr::video::SColor(255,255,0,255));
		m_core.m_driver->endScene();
	}
	m_run = true;
	_mapper->clear3dMap();
	_mapper->clear2dMap();
	block->remove();
	perso->remove();
}