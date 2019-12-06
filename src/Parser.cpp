#include "Parser.hpp"

Parser::Parser(std::string const & name, std::list<Command> &_commands)
{
	_file_read.open(name, std::ifstream::in);
	if (_file_read.is_open())
	{
		std::string line;
		for (;std::getline(_file_read, line);)
		{
			line = Trim(line);
			try
			{
				_commands.push_front(ParseCommand(line));
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
				exit(2);
			}
		}
		for (auto & elem : _commands)
		{
			std::cout << "Value: " <<  elem.GetValue() << "| Action: " << elem.GetAction() << std::endl;
		}
	}
	else
		throw Parser::InvalidFile();
}

Parser::Parser(std::list<Command> &_commands)
{
	std::string line;
	for (;std::getline(std::cin, line);)
	{
		if (line.find(";;") != std::string::npos)
			break;
		line = Trim(line);
		_commands.push_front(ParseCommand(line));
	}
	for (auto & elem : _commands)
	{
		std::cout << "Value: " <<  elem.GetValue() << "| Action: " << elem.GetAction() << std::endl;
	}
}



Parser::Parser(Parser const &)
{}

Parser::~Parser()
{
	_file_read.close();
}

const char* Parser::InvalidFile::what() const noexcept
{
	return "Invalid File";
}

const char* Parser::UnknownCommand::what() const noexcept
{
	return "Virtual machine doesn't know this command";
}

const char* Parser::SyntaxError::what() const noexcept
{
	return "Virtual machine detect syntax error";
}

std::string Parser::Trim(const std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

Command Parser::ParseCommand(std::string const &command)
{
	std::smatch					s_match;
	
	std::regex_match(command, s_match, std::regex("^(;|pop|dump|add|sub|mul|div|mod|print|exit|push|assert)(.)*"));
	if (s_match[1] != "")
	{
		Command new_command(s_match[1]);
		if (s_match[2] == "push" || s_match[2] == "assert")
		{
			std::regex_search(command, s_match, std::regex("[\\ ](int8|int16|int32)[\\(]([-]?\\d+)[\\)]|[\\ ](float|double)[\\(]([-]?\\d+[\\.]?\\d+)[\\)]"));
			if (s_match[2] == "" && s_match[4] == "")
				throw SyntaxError();
			(s_match[2] == "") ? new_command.SetValue(s_match[4]) : new_command.SetValue(s_match[2]);
		}
		return new_command;
	}
	throw UnknownCommand();
}


