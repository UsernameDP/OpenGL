#pragma once
#include <iostream>
#include <string>

inline void throwRunTimeError(const std::string description, const char* file, const int line) {
	throw std::runtime_error(file + std::string("\tline ") + std::to_string(line) + std::string("\nDescription : ") + description);
}

#ifndef THROW_RUNTIME_ERROR 
#define THROW_RUNTIME_ERROR(content) throwRunTimeError(content, __FILE__, __LINE__)
#endif