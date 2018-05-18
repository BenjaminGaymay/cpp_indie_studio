/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Options
*/

#pragma once

#include <iostream>

class Options {
public:
	Options(const std::size_t width, const std::size_t height, const bool fullscren) :
		m_width(width), m_height(height), m_fullscren(fullscren) {};
	~Options() {};

	std::size_t getWidth() const {
		return m_width;
	};
	std::size_t getHeight() const {
		return m_height;
	}
	bool getFullScreen() const {
		return m_fullscren;
	}

private:
	std::size_t m_width;
	std::size_t m_height;
	bool m_fullscren;
};
