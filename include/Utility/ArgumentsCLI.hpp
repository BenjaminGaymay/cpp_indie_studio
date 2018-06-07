//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ArgumentsCLI
//

#pragma once

#include <vector>
#include <iostream>
#include <functional>

struct ArgumentsCLI {
public:
	ArgumentsCLI();
	ArgumentsCLI(std::pair<std::string, std::string> args, std::function<void(void)> function) : Args(args), Function(function) {}
	ArgumentsCLI(std::pair<std::string, std::string> args) : Args(args){}
	~ArgumentsCLI() {};

	std::pair<std::string, std::string> Args;
	std::function<void(void)> Function;
};
