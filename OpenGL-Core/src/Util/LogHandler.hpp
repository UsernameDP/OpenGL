#pragma once
#include <iostream>
#include <string>

namespace exd
{
	// ANSI escape codes
	namespace TextColor
	{
		static const char *RESET = "\033[0m";
		static const char *RED = "\033[31m";
		static const char *YELLOW = "\033[33m";
		static const char *GREEN = "\033[32m";
		static const char *BLUE = "\033[34m";
		static const char *LIGHT_BLUE = "\033[94m";
	};

	inline void exit_error(const std::string description, const char *file, const int line)
	{
		std::cerr << TextColor::RED << std::string("EXIT_ERROR : ") + "|" + description + "|\n" + file + std::string("\tline ") + std::to_string(line) << TextColor::RESET;
		std::exit(1);
	}
	inline void warning(const std::string description, const char *file, const int line)
	{
		std::cerr << TextColor::YELLOW << std::string("ERROR : ") + "|" + description + "|\n" + file + std::string("\tline ") + std::to_string(line) << TextColor::RESET
				  << std::endl;
	}
	inline void throw_runtime_error(const std::string description, const char *file, const int line)
	{
		throw std::runtime_error(
			TextColor::RED +
			std::string("RUNTIME_ERROR : ") +
			"|" +
			description +
			"|\n" +
			file +
			std::string("\tline ") +
			std::to_string(line) +
			TextColor::RESET);
	}

	inline void log(const std::string description, const char *file, const int line)
	{
		std::cout << TextColor::LIGHT_BLUE << std::string("LOG : ") + "|" + description + "|\n" + file + std::string("\tline ") + std::to_string(line)
				  << std::endl
				  << TextColor::RESET;
	}

	inline void log_success(const std::string description, const char *file, const int line)
	{
		std::cout << TextColor::GREEN << std::string("SUCCESS : ") + "|" + description + "|\n" + file + std::string("\tline ") + std::to_string(line)
				  << std::endl
				  << TextColor::RESET;
	}
}


#ifdef VERSION_RELEASE // if you have the RELEASE macro, then debugs don't print
#define EXIT_ERROR(content) exd::exit_error(content, __FILE__, __LINE__);
#define WARNING(content) exd::warning(content, __FILE__, __LINE__);
#define THROW_RUNTIME_ERROR(content) exd::throw_runtime_error(content, __FILE__, __LINE__)
#define LOG(content)
#define LOG_SUCCESS(content)
#define LOG_CONSTRUCTOR(className)
#define LOG_DESTRUCTOR(className)
#else
#define EXIT_ERROR(content) exd::exit_error(content, __FILE__, __LINE__);
#define WARNING(content) exd::warning(content, __FILE__, __LINE__);
#define THROW_RUNTIME_ERROR(content) exd::throw_runtime_error(content, __FILE__, __LINE__)
#define LOG(content) exd::log(content, __FILE__, __LINE__)
#define LOG_SUCCESS(content) exd::log_success(content, __FILE__, __LINE__)
#define LOG_CONSTRUCTOR(className) exd::log_success(std::string(className) + std::string(" constructor completed"), __FILE__, __LINE__)
#define LOG_DESTRUCTOR(className) exd::log_success(std::string(className) + std::string(" destructor completed"), __FILE__, __LINE__)

#endif