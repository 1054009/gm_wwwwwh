#pragma once

#include <string>

class IOFile
{
public:
	std::string m_strPath = "";

	std::string read();
	bool write(std::string data);
	bool append(std::string data);
};