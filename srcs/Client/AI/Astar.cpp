/*
** EPITECH PROJECT, 2018
** test
** File description:
** Path
*/

#include "Astar.hpp"

Pos &Pos::operator=(const Pos &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

bool Pos::operator==(const Pos &rhs) const
{
	return x == rhs.x && y == rhs.y;
}

Pos operator+(const Pos &lhs, const Pos &rhs)
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

void Astar::populateGrid()
{
	_rows = static_cast<int>(_map.size());
	_cols = static_cast<int>(_map[0].size());
	_grid.resize(_rows);
	for (int y = 0; y < _rows; y++)
		for (int x = 0; x < _cols; x++)
			_grid[y].push_back(Node(x, y));
}

void Astar::showGrid()
{
	for (auto &line : _grid) {
		for (auto &cell : line) {
			// std::cout << cell.pos.x << " " << cell.pos.y << "  ";
			std::cout << cell.f << "  ";
		}
		std::cout << std::endl;
	}
}

bool Astar::isInList(const std::list<Node*> &set, const Node &node)
{
	for (const auto &el : set)
		if (node.pos == el->pos)
			return true;
	return false;
}

double Astar::heuristic(const Pos &p1, const Pos &p2)
{
	return abs(p2.y - p1.y) + abs(p2.x + p1.x);
}

void Astar::clearVector()
{
	if (!_path.empty())
		_path.clear();
	if (!_openSet.empty())
		_openSet.clear();
	if (!_closedSet.empty())
		_closedSet.clear();
}

std::vector<Pos> Astar::findPath(const Pos &start, const Pos &goal)
{
	Node *current = nullptr;
	Node *neighbor = nullptr;
	Pos tmp;
	int tempG;

	clearVector();
	_openSet.push_back(&_grid[start.y][start.x]);
	while (!_openSet.empty()) {
		current = *_openSet.begin();
		for (auto &el : _openSet)
			if (el->f < current->f)
				current = el;
		if (current->pos == goal) {
			_path.push_back(current->pos);
			while (current->parent) {
				_path.push_back(current->parent->pos);
				current = current->parent;
			}
			break;
		}
		_closedSet.push_back(current);
		_openSet.erase(std::find(_openSet.begin(), _openSet.end(), current));;
		for (std::size_t i = 0; i < _dirs.size(); i++) {
			tmp = current->pos + _dirs[i];
			if (tmp.x < 0 or tmp.y < 0 or tmp.x >= _cols or tmp.y >= _rows or _map[tmp.y][tmp.x] == '#')
				continue;
			neighbor = &_grid[tmp.y][tmp.x];
			if (isInList(_closedSet, *neighbor))
				continue;
			tempG = current->g + 1;
			if (isInList(_openSet, *neighbor)) {
				if (tempG < neighbor->g)
					neighbor->g = tempG;
			} else {
				neighbor->g = tempG;
				_openSet.push_back(neighbor);
			}
			neighbor->h = heuristic(neighbor->pos, goal);
			neighbor->f = neighbor->h + neighbor->g;
			neighbor->parent = current;
		}
	}
	return _path;
}