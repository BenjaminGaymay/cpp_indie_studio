/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Clock
*/

#pragma once

#include <chrono>

namespace Indie {
	struct Clock {
	public:
		Clock();
		~Clock();
		int getElapsedTime();
		void reset();

	private:
		time_t m_start;
	};
}