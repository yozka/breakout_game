#pragma once
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

namespace dm
{

	std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems, const bool autotrim = false);
	std::vector<std::string> split(const std::string &s, char delim, const bool autotrim = false);

	std::string toLower(const std::string &value);
	std::string toUpper(const std::string &value);
	bool replace(std::string& str, const std::string& from, const std::string& to);
}