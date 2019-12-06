#include "main.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{
	std::string command;
	try
	{
		if (argc > 1)
		{
			for (int i = 1; i < argc; i++)
			{
				Parser parser(argv[i]);
				
			}
		}
		else
		{
			Parser parser;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(2);
	}
	return 0;
}