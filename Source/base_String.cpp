// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "base_String.h"
#include <sstream>

using namespace dm;


	std::vector<std::string>& dm::split(const std::string &s, char delim, std::vector<std::string> &elems, const bool autotrim)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
		{
            //fix const bool autotrim
            {
                elems.push_back(item);
            }
		}
		return elems;
	}


	//------------------------------------------------------------------------------------------------------------
	std::vector<std::string> dm::split(const std::string &s, char delim, const bool autotrim)
	{
		std::vector<std::string> elems;
		dm::split(s, delim, elems);
		return elems;
	}



	//------------------------------------------------------------------------------------------------------------
	std::string dm::toLower(const std::string &value)
	{
		std::string s;
		s.resize(value.size());

		std::transform(value.cbegin(), value.cend(), s.begin(),	::tolower);
		return s;
	}



	//------------------------------------------------------------------------------------------------------------
	std::string dm::toUpper(const std::string &value)
	{
		std::string s;
		s.resize(value.size());

		std::transform(value.cbegin(), value.cend(), s.begin(), ::toupper);
		return s;
	}


	bool dm::replace(std::string& str, const std::string& from, const std::string& to) 
	{
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}
