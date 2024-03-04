#include "wwwwwh/library/io/iofile.h"

#include <filesystem>
#include <fstream>

std::string IOFile::read()
{
	if (!std::filesystem::exists(this->m_strPath))
		return "";

	std::ostringstream stream = std::ostringstream();
	std::ifstream fileStream(this->m_strPath);

	if (fileStream.is_open())
	{
		stream << fileStream.rdbuf();
		fileStream.close();
	}

	return stream.str();
}

bool IOFile::write(std::string data)
{
	std::ofstream fileStream(this->m_strPath);

	if (fileStream.is_open())
	{
		fileStream << data;
		fileStream.close();

		return true;
	}

	return false;
}

bool IOFile::append(std::string data)
{
	std::ofstream fileStream(this->m_strPath, std::ios_base::app);

	if (fileStream.is_open())
	{
		fileStream << data;
		fileStream.close();

		return true;
	}

	return false;
}