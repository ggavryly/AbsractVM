#include "AVM.hpp"

AVM::AVM(int argc, char **argv) : _argc(argc) , _argv(argv)
{}

AVM::AVM(AVM const &)
{}

AVM::~AVM()
{}

void AVM::Parse()
{
	try
	{
		if (_argc > 1)
		{
			for (int i = 1; i < _argc; i++)
			{
				Parser parser(_argv[i], _commands);
			}
		}
		else
		{
			Parser parser(_commands);
		}
	}
	catch (std::exception &e)
	{
		std::cout << "AVM::Parse::" << e.what() << std::endl;
		exit(1);
	}
}