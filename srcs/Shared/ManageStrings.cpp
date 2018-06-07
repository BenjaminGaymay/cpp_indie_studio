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

std::string ManageStrings::replaceStr(std::string oldStr, std::string newStr, char *cStr)
{
	size_t index = 0;
	size_t oldStrLen = oldStr.length();
	std::string str = std::string(cStr);

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

std::vector<std::string> ManageStrings::splitString(const std::string &str, char separator)
{
	std::string tmp;
	std::vector<std::string> splited;

	for (auto &c: str) {
		if (c != separator)
			tmp += c;
		else if (c == separator && !tmp.empty()) {
			splited.push_back(tmp);
			tmp.clear();
		}
	}
	if (!tmp.empty())
		splited.push_back(tmp);
	return splited;
}

bool ManageStrings::isInteger(std::string &str)
{
	if (str.empty())
		return false;
	for (auto &c : str) {
		if (!isdigit(c))
			return false;
	}
	return true;
}

std::string ManageStrings::convertWchart(const wchar_t *msg)
{
	std::wstring t(msg);
	std::string res(t.begin(), t.end());

	return res;
}