/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** LocalGame
*/

#include "Core.hpp"
#include "GameBackUp.hpp"
#include "LocalGame.hpp"

Indie::LocalGame::LocalGame()
{}

Indie::LocalGame::~LocalGame()
{}

void Indie::Core::saveLocalGame(std::vector<std::string> &infos)
{
	std::string gameInfo = infos[0];
	GameBackUp backup;
	auto &afile = backup.getFileEditor();

	if (!infos.empty()) {
		std::replace(gameInfo.begin(), gameInfo.end(), '>', ':');
		std::replace(gameInfo.begin(), gameInfo.end(), '|', '\n');
		afile << gameInfo << std::endl;
	}
	backup.player(_playerObjects[0], _mapper);
	backup.map(_mapper->getMap2d());
}