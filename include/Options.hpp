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
	m_width(0), m_height(0), m_fullscreen(false), m_splashscreen(true), m_launch(true), m_music(true) {}
	Options(const std::size_t width, const std::size_t height, const bool fullscreen, const bool splash, const bool music) :
		m_width(width), m_height(height), m_fullscreen(fullscreen), m_splashscreen(splash), m_launch(true), m_music(music) {};
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

	bool getSplashScreen() const {
		return m_splashscreen;
	}

	bool getLaunch() const {
		return m_launch;
	}

	bool getMusic() const {
		return m_music;
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

	void setSplashScreen(bool splash) {
		m_splashscreen = splash;
	}

	void setLaunch(bool launch) {
		m_launch = launch;
	}

	void setMusic(bool music) {
		m_music = music;
	}

private:
	std::size_t m_width;
	std::size_t m_height;
	bool m_fullscreen;
	bool m_splashscreen;
	bool m_launch;
	bool m_music;
};
