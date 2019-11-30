#pragma once
#include "main.hpp"
class Parser
{
public:
	Parser(std::string const & name);
	
	Parser();
	
	std::string Trim(const std::string & str);
	
	Parser(Parser const &);
	
	~Parser();

private:
	std::ifstream					_file_read;
	std::forward_list<std::string>	_commands;
	
private:
	class InvalidFile : public std::exception
	{
		const char* what() const noexcept;
	};
	class NoExitCommand : public std::exception
	{
		const char* what() const noexcept;
	};
};

