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
		std::vector<std::string> &directories,
		const std::string &parentDir,
		const std::vector<std::string> &names,
		const bool &recursive = false)
	{
		if (!dirExists(parentDir)) {
			THROW_RUNTIME_ERROR(parentDir + "\t does not exist or is not a directory");
		}

		for (const auto &entry : fs::directory_iterator(parentDir))
		{
			if (entry.is_directory())
			{
				for (const std::string &name : names)
				{
					if (getFileOrDirectoryName(entry.path().string()) == name)
					{
						directories.push_back(entry.path().string());
					}
					else if (recursive)
					{
						getAllDirectoryWithNames(directories, entry.path().string(), names, recursive);
					}
				}
			}
		}
	}

	inline void getAllFilesWithNames(
		std::vector<std::string>& files,
		const std::string& parentDir,
		const std::vector<std::string>& names,
		const bool& recursive = false)
	{
		if (!dirExists(parentDir)) {
			THROW_RUNTIME_ERROR(parentDir + "\t does not exist or is not a directory");
		}

		for (const auto& entry : fs::directory_iterator(parentDir))
		{
			if (entry.is_regular_file())
			{
				fs::path filePath = entry.path();

				for (const std::string& name : names)
				{
					if (filePath.filename().string() == name)
					{
						files.push_back(entry.path().string());
					}
				}
			}
			else if (recursive)
			{
				getAllFilesWithNames(files, entry.path().string(), names, recursive);
			}
		}
	}

	/*Extensions*/
	inline void filesWithExtensions(
		std::vector<std::string> &files,
		const std::string & parentDir,
		const std::vector<std::string> &extensions,
		const bool &recursive = false)
	{

		if (!dirExists(parentDir))
		{
			THROW_RUNTIME_ERROR(parentDir + "\t does not exist or is not a directory");
		}

		for (const auto &entry : fs::directory_iterator(parentDir))
		{
			if (entry.is_regular_file())
			{
				for (const std::string &extension : extensions)
				{
					if (entry.path().extension() == extension)
					{
						files.push_back(entry.path().string());
					}
				}
			}
			else if (recursive)
			{
				filesWithExtensions(files, entry.path().string(), extensions, true);
			}
		}
	}

}