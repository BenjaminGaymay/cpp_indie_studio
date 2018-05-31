//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Clock
//

#pragma once

#include <chrono>

namespace Indie {
	struct Clock {
	public:
		Clock();
		~Clock();
		std::size_t getElapsedTime();
		void reset();

	private:
		std::chrono::time_point<std::chrono::system_clock> m_start;
	};
}