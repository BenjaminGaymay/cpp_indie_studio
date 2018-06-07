//
// EPITECH PROJECT, 2018
// student
// File description:
// 06/06/18
//

#pragma once

#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "Player.hpp"

namespace Indie {
	class GameBackUp {
	public:
		GameBackUp()
		{
			createFile();
		}
		~GameBackUp() {
			if (_file.is_open())
				_file.close();
		}
		std::vector<std::string> openFile(const std::string &fileName)
		{
			std::string str;
			std::vector<std::string> content;
			std::fstream file(_gamePath + fileName);

			if (!file.is_open())
				throw std::logic_error("GameBackUp: File not found.");
			while (std::getline(file, str)) {
				file >> str;
				content.emplace_back(str);
			}
			return content;
		}
		std::fstream &getFileEditor() { return _file; };
		bool createFile()
		{
			std::string fileName = _gamePath + "game-";
			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);
			std::ostringstream oss;
			oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
			auto str = oss.str();
			_file.open(fileName + str, std::fstream::out);
			return _file.is_open();
		}

		/**
		 * @brief must be the last function call of the backup
		 * @param aMap
		 */
		void map(std::vector<std::vector<int>> &aMap)
		{
			bool sep = false;

			_file << "MAP:" << std::endl;
			for (auto &line : aMap) {
				if (sep)
					_file << std::endl;
				sep = false;
				for (auto &block : line) {
					if (sep)
						_file << " ";
					_file << std::setfill('0') << std::setw(2) << block;
					sep = true;
				}
			}
			_file.close();
		}
		void player(const std::unique_ptr<Player> &player, const std::unique_ptr<Map> &_mapper)
		{
			auto pos3d = player->getPosition();
			auto pos2d = _mapper->get2dBlock(pos3d + _mapper->getSize() / 2);
			_file << "PLAYER:"
				<< player->getId() << ":"
				<< pos2d.X << ":" << pos2d.Y << ":"
				//<< pos3d.X << ":" << pos3d.Y << ":" << pos3d.Z << ":"
				<< player->getRotation().Y << ":"
				<< player->getSpeed() << ":"
				<< player->getPower() << ":"
				<< player->getBombNumber() << ":"
				<< player->getWallUp() << std::endl;
		}
	private:
		std::fstream _file;
		const std::string _gamePath = "games/";
	};
}
