//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Clock
//

#include "Clock.hpp"

Indie::Clock::Clock()
{
	m_start = std::chrono::system_clock::now();
}

Indie::Clock::~Clock()
{}

std::size_t Indie::Clock::getElapsedTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - m_start).count();
}

void Indie::Clock::reset()
{
	m_start = std::chrono::system_clock::now();
}