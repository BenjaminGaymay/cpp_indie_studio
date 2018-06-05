/*
** EPITECH PROJECT, 2018
** test
** File description:
** Path
*/

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <set>

using MapStr = std::vector<std::string>;
using MapBool = std::vector<std::vector<bool>>;

struct Pos {
public:
	Pos() = default;
	Pos(const int &x, const int &y) : x(x), y(y) {}
	Pos(const Pos &pos) : x(pos.x), y(pos.y) {}
	int x;
	int y;
	Pos &operator=(const Pos &);
	bool operator==(const Pos &) const;
};

Pos operator+(const Pos &, const Pos &);

struct Node {
public:
	Node() : pos(0,0), h(0), g(0), f(0), parent(nullptr) {};
	Node(const int &x, const int &y) : pos(x, y), h(0), g(0), f(0), parent(nullptr) {}
	Pos pos;
	double h;
	double g;
	double f;
	Node *parent;
	bool operator==(const Node &rhs)
	{
		return pos == rhs.pos;
	}
};

 using NodeSet = std::set<Node*>;
using MapNode = std::vector<std::vector<Node>>;

class Astar {
public:
	Astar() {}
	Astar(const MapStr &map) : _map(map) {
		populateGrid();
	}
	std::vector<Pos> findPath(const Pos &, const Pos &);
	void populateGrid();
	void setMap(const MapStr &map) {
		_map = map;
		populateGrid();
	}
	void showGrid();
	bool isInList(const std::list<Node*> &, const Node &);
	double heuristic(const Pos &, const Pos &);
	void clearVector();
	MapStr _map;
	std::vector<Pos> _dirs = {{-1, 0},{0, -1},{1, 0},{0, 1}};
	std::list<Node*> _openSet;
	std::list<Node*> _closedSet;
	std::vector<Pos> _path;
	MapNode _grid;
	int _cols;
	int _rows;
};