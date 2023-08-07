#pragma once
#include "LogHandler.hpp"
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace exd
{
	/*Basic*/
	inline std::string readFile(const std::string &path)
	{
		std::string data;
		std::string line;

		std::ifstream file(path);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				data += line + "\n";
			}

			file.close();
		}
		else
		{
			file.close();
			THROW_RUNTIME_ERROR("Can't find" + path);
		}

		return data;
	}
	inline void writeFile(const std::string &path, std::string data)
	{
		std::ofstream file(path);

		if (file.is_open())
		{
			file << data;

			file.close();
		}
		else
		{
			file.close();
			THROW_RUNTIME_ERROR("Can't find" + path);
		}
	}
	inline bool fileExists(const std::string &path)
	{
		fs::path file = static_cast<fs::path>(path);
		return fs::exists(file) && fs::is_regular_file(file);
	}
	inline bool dirExists(const std::string &path)
	{
		fs::path dir = static_cast<fs::path>(path);
		return fs::exists(dir) && fs::is_directory(dir);
	}

	/*Extension of fs*/
	inline std::string getFileOrDirectoryName(const std::string &path)
	{
		size_t found = path.find_last_of("/\\");

		return path.substr(found + 1);
	}
	inline std::string getRelative(const std::string& childPath, const std::string& parentPath) {
		fs::path parentPath_path = static_cast<fs::path>(parentPath);
		fs::path childPath_path = static_cast<fs::path>(childPath);

		fs::path relativePath = fs::relative(childPath_path, parentPath_path);

		if (!relativePath.empty()) {
			return relativePath.string();
		}
		return "";
	}

	/*Directories*/
	inline void getAllDirectoryWithNames(
		std::vector<std::string> &arr,
		const std::string &parentDir,
		const std::vector<std::string> &names,
		const bool &recursive = false)
	{

		for (const auto &entry : fs::directory_iterator(parentDir))
		{
			if (entry.is_directory())
			{
				for (const std::string &name : names)
				{
					if (getFileOrDirectoryName(entry.path().string()) == name)
					{
						arr.push_back(entry.path().string());
					}
					else if (recursive)
					{
						getAllDirectoryWithNames(arr, entry.path().string(), names, recursive);
					}
				}
			}
		}
	}

	/*Extensions*/
	inline void filesWithExtensions(
		std::vector<std::string> &arr,
		const std::string &dirPath,
		const std::vector<std::string> &extensions,
		const bool &recursive = false)
	{

		if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
		{
			THROW_RUNTIME_ERROR(dirPath + "\t does not exist or is not a directory");
		}

		for (const auto &entry : fs::directory_iterator(dirPath))
		{
			if (entry.is_regular_file())
			{
				for (const std::string &extension : extensions)
				{
					if (entry.path().extension() == extension)
					{
						arr.push_back(entry.path().string());
					}
				}
			}
			else if (recursive)
			{
				if (entry.is_directory() && entry.exists())
				{
					filesWithExtensions(arr, entry.path().string(), extensions, true);
				}
			}
		}
	}

}