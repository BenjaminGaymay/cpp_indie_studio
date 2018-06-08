//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Multiplayer
//

#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>
#include "Player.hpp"
#include "ManageStrings.hpp"

void Indie::Core::readServerInformations(std::vector<std::string> servSend)
{
	std::vector<std::string> infos;
	ObjectsType type;
	ObjectsEvents event;

	for (auto &line : servSend) {
		std::cerr << "CLIENT: " << line << std::endl;
		infos = ManageStrings::splitString(line, ':');
		if (infos.size() >= 2 && ManageStrings::isInteger(infos[0]) && ManageStrings::isInteger(infos[1])) {
			type = static_cast<ObjectsType>(std::stoi(infos[0]));
			event = static_cast<ObjectsEvents>(std::stoi(infos[1]));
			infos.erase(infos.begin(), infos.begin() + 2);
			(this->*_objectsFct[type])(event, infos);
		}
	}
}

int Indie::Core::waitForId()
{
	std::vector<std::string> servSend;
	int id;

	while (servSend.empty())
		servSend = _socket->readSocket();
	for (auto &c : servSend[0])
		if (!isdigit(c))
			throw std::runtime_error("Communication error");

	id = std::stoi(servSend[0]);
	servSend.erase(servSend.begin());
	readServerInformations(servSend);
	return id;
}

void Indie::Core::sendMapToServer(const std::string &path)
{
	std::string map;
	FILE *file = fopen(path.c_str(), "r");
	char *buffer = nullptr;
	std::size_t size = 0;

	if (!file)
		throw std::runtime_error("Error: can't open map.");
	while (getline(&buffer, &size, file) > 0) {
		buffer[strlen(buffer) - 1] = '\0';
		map += std::string(buffer) + ":";
	}
	dprintf(_socket->getFd(), "2:0:%s\n", map.c_str());
	free(buffer);
	fclose(file);
}