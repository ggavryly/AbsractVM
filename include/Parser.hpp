#pragma once
#include "main.hpp"
#include "Command.hpp"
class Parser
{
public:
	Parser(std::string const & name, std::list<Command> &_commands);
	
	Parser(std::list<Command> &_commands);
	
	std::string Trim(const std::string & str);
	
	Command ParseCommand(std::string const &);
	
	Parser(Parser const &);
	
	~Parser();

private:
	std::ifstream					_file_read;
	
private:
	class InvalidFile : public std::exception
	{
		const char* what() const noexcept;
	};
	class UnknownCommand : public std::exception
	{
		const char* what() const noexcept;
	};
	class SyntaxError : public std::exception
	{
		const char* what() const noexcept;
	};
};

