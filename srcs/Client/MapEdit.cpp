//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// MapEdit
//

#include "Core.hpp"
#include <random>

void Indie::Core::createRandMap(std::string name, size_t x, size_t y)
{
	std::string file = "assets/maps/" + name;
	std::vector<std::vector<int>> map;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,1);

	if (x < 10 || y < 10 || x > 50 || y > 50) {
		std::cerr << "x and y minimum values are 10" << std::endl;
		exit(0);
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
	map[1][1] = 0;
	map[1][2] = 0;
	map[2][1] = 0;

	// TOP RIGHT CORNER
	map[1][x - 2] = 0;
	map[1][x - 3] = 0;
	map[2][x - 2] = 0;

	// BOT LEFT CORNER
	map[y - 2][1] = 0;
	map[y - 2][2] = 0;
	map[y - 3][1] = 0;

	// BOT RIGHT CORNER
	map[y - 2][x - 2] = 0;
	map[y - 2][x - 3] = 0;
	map[y - 3][x - 2] = 0;

	writeInFile(file, map);
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
			outfile << "0" << map[i][j] << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}

void Indie::Core::cleanMap()
{
	size_t min = _mapper->getMap2d()[0].size();
	size_t max = 0;

	for (size_t i = 0; i < 50; ++i) {
		for (size_t j = 0; j < 50; ++j) {
			std::cout << _mapper->getMap2d()[i][j];
		}
		std::cout << std::endl;
	}
	int x = 0;
	for (size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		for (size_t j = 0; j < _mapper->getMap2d()[i].size(); ++j)
			if (_mapper->getMap2d()[i][j] == 1)
				x += 1;
		if (x > 0)
			break;
	}
	if (x == 0)
		return ;
	while (std::find(std::begin(_mapper->getMap2d()[0]), std::end(_mapper->getMap2d()[0]), 1) != std::end(_mapper->getMap2d()[0]))
		_mapper->getMap2d().erase(_mapper->getMap2d().begin());
	int i = _mapper->getMap2d().size() - 1;
	while (std::find(std::begin(_mapper->getMap2d()[i]), std::end(_mapper->getMap2d()[i]), 1) != std::end(_mapper->getMap2d()[i])) {
		_mapper->getMap2d().erase(_mapper->getMap2d().end());
		--i;
	}
	for (size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		for (size_t j = 0; j < _mapper->getMap2d()[i].size(); ++j) {
			if (_mapper->getMap2d()[i][j] == 1 && min > j) {
				min = j;
				break;
			}
		}
		for (size_t j = _mapper->getMap2d()[i].size() - 1; j > 0; --j) {
			if (_mapper->getMap2d()[i][j] == 1 && max < j) {
				max = j + 1;
				break;
			}
		}
	}
	for (size_t i = 0; i < _mapper->getMap2d().size(); ++i) {
		_mapper->getMap2d()[i].erase(_mapper->getMap2d()[i].begin() + max, _mapper->getMap2d()[i].end());
		_mapper->getMap2d()[i].erase(_mapper->getMap2d()[i].begin(), _mapper->getMap2d()[i].begin() + min);
	}
}

int Indie::Core::editMapEvents()
{
	if (m_event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (m_event.isKeyDown(irr::KEY_KEY_S)) {
		cleanMap();
		return -1;
	}
	if (m_event.MouseState.LeftButtonDown == true) {

		m_event.MouseState.LeftButtonDown = false;
		int x = int((m_event.MouseState.Position.X - 362) / 14);
		int y = int((m_event.MouseState.Position.Y - 12) / 14);
		if (x >= 0 && y >= 0 && x < 50 && y < 50)
			_mapper->getMap2d()[y][x] = (_mapper->getMap2d()[y][x] == 1 ? _mapper->getMap2d()[y][x] = 0 : _mapper->getMap2d()[y][x] = 1);
		// for (size_t i = 0; i < 50; ++i) {
		// 	for (size_t j = 0; j < 50; ++j) {
		// 		std::cout << _mapper->getMap2d()[i][j];
		// 	}
		// 	std::cout << std::endl;
		//}
	}
	return 0;
}

void Indie::Core::editMap()
{
	m_core.editMapView(m_event);
	createZeroMap("mdr.txt", 50, 50);
	_mapper = std::make_unique<Map>("assets/maps/mdr.txt", 20.0f, 100.0f, _graphism);
	std::vector<std::vector<int>> mdr = _mapper->getMap2d();
	while (m_core.m_device->run() && m_run) {
		if (editMapEvents() == -1)
			break;
		m_core.m_driver->beginScene(true, true, _color);
    		m_core.m_sceneManager->drawAll();
		m_core.m_driver->endScene();
	}
}