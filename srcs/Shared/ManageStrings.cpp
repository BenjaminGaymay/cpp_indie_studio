//
// EPITECH PROJECT, 2018
// arcade
// File description:
// manageStrings
//

#include <iostream>
#include <vector>
#include "ManageStrings.hpp"

std::string ManageStrings::replaceStr(std::string oldStr, std::string newStr, std::string &str)
{
	size_t index = 0;
	size_t oldStrLen = oldStr.length();

	while (true) {
		index = str.find(oldStr, 0);
		if (index == std::string::npos)
			break;
		str.replace(index, oldStrLen, newStr);
		index += oldStrLen;
	}
	return str;
}

std::string ManageStrings::lstrip(std::string &str)
{
	std::string::iterator it = str.begin();

	replaceStr("\t", " ", str);
	for (auto &c : str) {
		if (c == ' ')
			it += 1;
		else
			break;
	}
	str.erase(str.begin(), it);
	return str;
}

std::vector<std::string> ManageStrings::splitString(std::string str, char separator)
{
	std::string tmp = "";
	std::vector<std::string> splited;

	for (auto c: str) {
		if (c != separator)
			tmp += c;
		else if (c == separator && tmp != "") {
			splited.push_back(tmp);
			tmp = "";
		}
	}
	if (tmp != "")
		splited.push_back(tmp);
	return splited;
}
