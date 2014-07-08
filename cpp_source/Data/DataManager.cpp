#include "DataManager.h"

#include <filesystem>

bool DataManager::LoadFile(const std::string& filename)
{
	std::tr2::sys::path path = filename;
	if (std::tr2::sys::exists(path) == false)
	{
		return false;
	}

	return true;
}