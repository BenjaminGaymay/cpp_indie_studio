//
// EPITECH PROJECT, 2018
// student
// File description:
// 07/06/18
//

#include "GameBackUp.hpp"
#include "Core.hpp"

void Indie::Core::loadLocalGame(const std::string &fileName)
{
	GameBackUp backup;

	auto content = backup.openFile(fileName);
	std::vector<std::string> object;

	for (auto elem = content.begin() ; elem != content.end() ; ++elem) {
		auto line = *elem;
		if (line.substr(0, 3) == "MAP") {
			content.erase(elem); // content keep just the map, that all
			break;
		} else {
			object.push_back(line); //push object (bomb, player, bot)
			content.erase(elem); //filter, just keep map content
		}

	}
	if (content.empty() || object.empty()) //if map is empty or if any player on map...
		throw std::logic_error("Corrupted BackUp");
	std::string map;
	bool sep = false;
	for (auto &row : content) {
		if (sep)
			map += ":";
		map += row;
		sep = true;
	}
	_socket->sendInfos(MAP, APPEAR, map); // normalement le serv va sauvegarder puis remplacer les 10 par des 00;
	for (const auto &line : object) {
		std::string part = line.substr(0, line.find(':'));
		if (part == "BOMB") {
			_socket->sendInfos(BOMB, CREATEBOMB, &line[part.size() + 1]);
		} else if (part == "PLAYER") {
			_socket->sendInfos(PLAYER, APPEAR, &line[part.size() + 1]);
		} else if (part == "BOT") {
			;
		}
	}
}

void Indie::Core::saveLocalGame(std::vector<std::string> &infos)
{
	auto &mapper = _game->getMapperEdit();
	std::string gameInfo = infos[0];
	GameBackUp backup;
	auto &afile = backup.getFileEditor();

	if (!infos.empty()) {
		std::replace(gameInfo.begin(), gameInfo.end(), '>', ':');
		std::replace(gameInfo.begin(), gameInfo.end(), '|', '\n');
		afile << gameInfo << std::endl;
	}
	backup.player(_playerObjects[0], mapper);
	backup.map(mapper->getMap2d()); // must be every time last call
}
