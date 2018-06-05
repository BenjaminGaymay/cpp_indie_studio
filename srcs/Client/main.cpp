//
// EPITECH PROJECT, 2018
// IndieStudio
// File description:
// main function
//

#include <algorithm>
#include "Core.hpp"
#include "ArgumentsCLI.hpp"

static void displayHelp(const char *prog)
{
	std::cout << "USAGE:\n\t" << prog << " [--help] [--nosplash] [--nomusic]\n"
		<< "\nDESCRIPTION:\n\t--help -h\tdisplay this help\n\t"
		<< "--nosplash -ns\tdisable splashscreen\n\t"
		<< "--nomusic -nm\tdisable audio" << std::endl;
}

static void checkArgs(int ac, char **av, Options &opt)
{
	std::vector<ArgumentsCLI> args;
	args.push_back(ArgumentsCLI({"--nosplash", "-ns"}, [&opt]() mutable {
		opt.setSplashScreen(false);
	}));
	args.push_back(ArgumentsCLI({"--nomusic", "-nm"}, [&opt]() mutable {
		opt.setMusic(false);
	}));
	args.push_back(ArgumentsCLI({"--help", "-h"}, [&opt, av]() mutable {
		opt.setLaunch(false);
		displayHelp(av[0]);
	}));

	for (int i = 1; i < ac; i++) {
		std::string tmp(av[i]);
		for (auto &c : args)
			if (tmp == c.Args.first or tmp == c.Args.second)
				c.Function();
	}
}

int main(int ac, char **av)
{
	Options opt(1280, 720, false, true, true);

	checkArgs(ac, av, opt);
	if (opt.getLaunch()) {
		Indie::Core core;
		core.init(opt);
		core.run();
	}
	return 0;
}
