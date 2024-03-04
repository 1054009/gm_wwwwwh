#pragma once

#include <string>
#include <tuple>
#include <vector>

class IODirectory
{
public:
	std::string m_strPath = "";

	std::tuple<std::vector<std::string>, std::vector<std::string>> read();
};