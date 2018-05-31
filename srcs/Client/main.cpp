//
// EPITECH PROJECT, 2018
// IndieStudio
// File description:
// main function
//

#include "Core.hpp"

int main()
{
	Indie::Core core;
	Options opt(1280, 720, false);

	core.init(opt);
	core.run();
	return 0;
}
