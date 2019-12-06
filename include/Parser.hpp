#pragma once
#include "main.hpp"
#include "Command.hpp"

class Parser
{

public:
	Parser(std::string const & name);
	
	Parser();
	
	std::string Trim(const std::string & str);
	
	Command ParseCommand(std::string const &);
	
	Parser(Parser const &);
	
	~Parser();

private:
	std::ifstream					_file_read;
	std::list<Command>				_commands;
	
private:
	class ParserError
	{
	public:
		ParserError();
		
		ParserError(ParserError const &);
		
		~ParserError();
	
	public:
		static bool ExitTest(std::list<Command> const &);
	};
	
private:
	class InvalidFile : public std::exception
	{
		const char* what() const noexcept;
	};
	class NoExitCommand : public std::exception
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

