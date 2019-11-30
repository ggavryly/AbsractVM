#include "Parser.hpp"

Parser::Parser(std::string const & name)
{
	_file_read.open(name, std::ifstream::in);
	if (_file_read.is_open())
	{
		std::string line = "";
		for (;std::getline(_file_read, line);)
		{
			line = Trim(line);
			std::cout << line;
		}
	}
	else
		throw Parser::InvalidFile();
}

Parser::Parser(Parser const &)
{}

Parser::~Parser()
{}

const char* Parser::InvalidFile::what() const noexcept
{
	return "Invalid File";
}

std::string Parser::Trim(const std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}