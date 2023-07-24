#pragma once
#include <iostream>
#include <string>

//ANSI escape codes
namespace TextColor {
	static const char* RESET = "\033[0m";
	static const char* RED = "\033[31m";
	static const char* GREEN = "\033[32m";

};

static inline void throwRunTimeError(const std::string description, const char* file, const int line) {
	throw std::runtime_error(
		std::string("RUNTIME_ERROR : ") +
		file +
		std::string("\tline ") +
		std::to_string(line) +
		std::string("\nDescription : ") +
		description);
}

static inline void log(const std::string description, const char* file, const int line) {
	std::cout << TextColor::GREEN <<
		std::string("LOG : ") +
		file +
		std::string("\tline ") +
		std::to_string(line) +
		std::string("\nDescription : ") +
		description << std::endl << TextColor::RESET;
}

#define THROW_RUNTIME_ERROR(content) throwRunTimeError(content, __FILE__, __LINE__)
#define LOG(content) log(content, __FILE__, __LINE__)