#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

namespace exd
{
	// Printing
	template <typename T>
	inline void printVector(const std::vector<T> &vector, bool commas = true, bool newline = false)
	{
		std::stringstream log;
		std::string additional = "";
		if (commas)
		{
			additional += " , ";
		}
		else
		{
			additional += " ";
		}

		if (newline)
		{
			additional += "\n";
		}

		for (int i = 0; i < vector.size() - 1; i++)
		{
			log << vector[i] << additional;
		}
		log << vector[vector.size() - 1] << std::endl;

		std::cout << log.str();
	}

	template <typename I, typename O>
	inline void printMap(const std::unordered_map<I, O> &map, bool commas = false, bool newline = true)
	{
		std::stringstream log;
		std::string additional = "";
		if (commas)
		{
			additional += " , ";
		}
		else
		{
			additional += " ";
		}

		if (newline)
		{
			additional += "\n";
		}

		for (const auto &pair : map)
		{
			log << "key : " << pair.first << "\tkey-value : " << pair.second << additional;
		}

		std::cout << log.str();
	}

	// String
	inline std::string toLowerCase(const std::string &str)
	{
		std::string result = str;
		for (char &c : result)
		{
			c = std::tolower(c);
		}
		return result;
	}
	inline void replaceWith(std::string &str, const std::string &replaceWhat, const std::string &replaceWith)
	{
		size_t pos = str.find(replaceWhat);
		size_t len = replaceWhat.length();

		if (pos != std::string::npos) // doesn't do anything if replace does not exist
		{
			str.replace(pos, len, replaceWith);
		}
	}
	inline std::string getReplaceAll(const std::string &str, const std::string &replaceWhat, const std::string &replaceWith)
	{
		std::string result = str;
		size_t pos = 0;

		while ((pos = result.find(replaceWhat, pos)) != std::string::npos)
		{
			result.replace(pos, replaceWhat.length(), replaceWith);
			pos += replaceWith.length(); // Move past the replacement
		}

		return result;
	}
	inline std::string trim(const std::string &str)
	{
		size_t start = str.find_first_not_of(" \t\n\r\f\v");
		if (start == std::string::npos)
		{
			return "";
		}

		size_t end = str.find_last_not_of(" \t\n\r\f\v");
		return str.substr(start, end - start + 1);
	}

	// unordered_map
	template <typename I, typename O>
	inline bool mapHas(std::unordered_map<I, O> map, const std::string &key)
	{
		if (map.count(key) > 0)
		{
			return true;
		}
		return false;
	}
}