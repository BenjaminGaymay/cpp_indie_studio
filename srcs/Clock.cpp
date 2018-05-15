/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Clock
*/

#include "Clock.hpp"

Indie::Clock::Clock()
{
	m_start = time(nullptr);
}

Indie::Clock::~Clock()
{}

int Indie::Clock::getElapsedTime()
{
	time_t stop = time(nullptr);
	int elapsed = stop - m_start;

	return elapsed;
}

void Indie::Clock::reset()
{
	m_start = time(nullptr);
}