#include "main.hpp"
#include "AVM.hpp"

int main(int argc, char **argv)
{
	AVM avm(argc, argv);
	avm.Execute();
	avm.Exit();
	return 0;
}