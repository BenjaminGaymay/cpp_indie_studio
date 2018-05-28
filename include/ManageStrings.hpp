//
// EPITECH PROJECT, 2018
// arcade
// File description:
// ManageStrings
//

#pragma once

class ManageStrings {
public:
	static std::string replaceStr(std::string, std::string, std::string &);
	static std::string lstrip(std::string &);
	static std::vector<std::string> splitString(std::string &, char);
	static bool isInteger(std::string &);
	static std::string convertWchart(const wchar_t *);
};