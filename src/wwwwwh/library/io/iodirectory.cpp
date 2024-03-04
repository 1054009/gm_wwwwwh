#include "wwwwwh/library/io/iodirectory.h"

#include <filesystem>

std::tuple<std::vector<std::string>, std::vector<std::string>> IODirectory::read()
{
	std::vector<std::string> files;
	std::vector<std::string> directories;

	// Invalid directory
	if (!std::filesystem::exists(this->m_strPath) || !std::filesystem::is_directory(this->m_strPath))
		return std::make_tuple(files, directories);

	const std::filesystem::path path(this->m_strPath);
	for (const std::filesystem::directory_entry& directoryEntry : std::filesystem::directory_iterator(path))
	{
		std::string entryPath(directoryEntry.path().string());

		if (directoryEntry.is_regular_file())
			files.push_back(entryPath);

		if (directoryEntry.is_directory())
			directories.push_back(entryPath);
	}

	return std::make_tuple(files, directories);
}