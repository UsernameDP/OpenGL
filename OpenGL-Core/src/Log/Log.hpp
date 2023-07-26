#pragma once
#include <iostream>
#include <string>

//ANSI escape codes
namespace TextColor {
	static const char* RESET = "\033[0m";
	static const char* RED = "\033[31m";
	static const char* GREEN = "\033[32m";
	static const char* BLUE = "\033[34m";
	static const char* LIGHT_BLUE = "\033[94m";
};

inline void throw_runtime_error(const std::string description, const char* file, const int line) {
	throw std::runtime_error(
		std::string("RUNTIME_ERROR : ") + 
		"|" + 
		description + 
		"|\n" +
		file +
		std::string("\tline ") +
		std::to_string(line));
}

inline void log(const std::string description, const char* file, const int line) {
	std::cout << TextColor::LIGHT_BLUE <<
		std::string("LOG : ") + 
		"|" + 
		description + 
		"|\n" + 
		file +
		std::string("\tline ") +
		std::to_string(line)
		<< std::endl << TextColor::RESET;
}

inline void log_success(const std::string description, const char* file, const int line) {
	std::cout << TextColor::GREEN <<
		std::string("SUCCESS : ") +
		"|" +
		description +
		"|\n" +
		file +
		std::string("\tline ") +
		std::to_string(line)
		<< std::endl << TextColor::RESET;
}


#define THROW_RUNTIME_ERROR(content) throw_runtime_error(content, __FILE__, __LINE__)
#define LOG(content) log(content, __FILE__, __LINE__)
#define LOG_SUCCESS(content) log_success(content, __FILE__, __LINE__)
#define LOG_CONSTRUCTOR(className) log_success(std::string(className) + std::string(" constructor completed"), __FILE__, __LINE__)
#define LOG_DESTRUCTOR(className) log_success(std::string(className) + std::string(" destructor completed"), __FILE__, __LINE__)