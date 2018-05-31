//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Options
//

#pragma once

#include <iostream>

class Options {
public:
	Options() :
	m_width(0), m_height(0), m_fullscreen(false) {}
	Options(const std::size_t width, const std::size_t height, const bool fullscreen) :
		m_width(width), m_height(height), m_fullscreen(fullscreen) {};
	~Options() {};

	std::size_t getWidth() const {
		return m_width;
	}

	std::size_t getHeight() const {
		return m_height;
	}

	bool getFullScreen() const {
		return m_fullscreen;
	}

	void setWidth(std::size_t width) {
		m_width = width;
	}

	void setHeight(std::size_t height) {
		m_height = height;
	}

	void setFullScreen(bool fullscreen) {
		m_fullscreen = fullscreen;
	}

private:
	std::size_t m_width;
	std::size_t m_height;
	bool m_fullscreen;
};
