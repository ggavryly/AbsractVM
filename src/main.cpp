#include "main.hpp"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::string command;
		for (int i = 1; i < argc; i++)
		{
			std::ifstream input_fd;
			input_fd.open(argv[i]);
			input_fd >> command;
		}
	}
	else
	{
		for (;std::string::getline();)
	}
	return 0;
}