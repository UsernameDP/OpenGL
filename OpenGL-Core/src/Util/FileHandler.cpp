#include "glpch.hpp"
#include "FileHandler.hpp"

std::string readFile(const std::string& path) {
	std::string data;
	std::string line;

	std::ifstream file(path);
	if (file.is_open()) {
			
		while (std::getline(file, line)) {
			data += line + "\n";
		}
		file.close();
	}
	else {
		file.close();
		THROW_RUNTIME_ERROR("Can't open " + path);
	}

	return data;
}