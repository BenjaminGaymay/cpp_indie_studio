//
// EPITECH PROJECT, 2018
// IndieStudio
// File description:
// main function
//

#include "Core.hpp"

int checkArgs(int ac, char **av, Options &opt)
{
	ac = ac;
	if (av[1] && std::string(av[1]).compare("--nosplash") == 0)
		opt.setSplashScreen(false);
	else if (av[1] && std::string(av[1]).compare("--help") == 0) {
		std::cout << "USAGE:\n\t./bomberman [--nosplash]\n\nDESCRIPTION\n\t--nosplash\tskip the splashscreen" << std::endl;
		opt.setLaunch(false);
	}
	return 0;
}

int main(int ac, char **av)
{
	Options opt(1280, 720, false, true);

	checkArgs(ac, av, opt);
	if (opt.getLaunch()) {
		Indie::Core core;
		core.init(opt);
		core.run();
	}
	return 0;
}
