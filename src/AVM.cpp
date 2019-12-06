#include "AVM.hpp"

AVM::AVM(int argc, char **argv) : _argc(argc) , _argv(argv)
{
	_func_with_args.insert(std::make_pair("push", &AVM::Push));
	_func_with_args.insert(std::make_pair("assert", &AVM::Assert));
	_func_without_args.insert(std::make_pair("pop", &AVM::Pop));
	_func_without_args.insert(std::make_pair("dump", &AVM::Dump));
	_func_without_args.insert(std::make_pair("add", &AVM::Add));
	_func_without_args.insert(std::make_pair("sub", &AVM::Sub));
	_func_without_args.insert(std::make_pair("mul", &AVM::Mul));
	_func_without_args.insert(std::make_pair("div", &AVM::Div));
	_func_without_args.insert(std::make_pair("mod", &AVM::Mod));
	_func_without_args.insert(std::make_pair("print", &AVM::Print));
	_func_without_args.insert(std::make_pair("exit", &AVM::Exit));
	_operand_factory.push_back(&AVM::CreateInt8);
	_operand_factory.push_back(&AVM::CreateInt16);
	_operand_factory.push_back(&AVM::CreateInt32);
	_operand_factory.push_back(&AVM::CreateFloat);
	_operand_factory.push_back(&AVM::CreateDouble);
}

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

void AVM::Execute()
{
	try
	{
		for(auto & elem : _commands)
		{
		
		}
	}
	catch (std::exception &e)
	{
		std::cout << "AVM::Execute::" << e.what() << std::endl;
		exit(2);
	}
}

IOperand const* AVM::CreateOperand(Type const &type, std::string const &value) const
{
	if (type == 0)
		AVM::CreateInt8(value);
	else if (type == 1)
		AVM::CreateInt16(value);
	else if (type == 2)
		AVM::CreateInt32(value);
	else if (type == 3)
		AVM::CreateFloat(value);
	else if (type == 4)
		AVM::CreateDouble(value);
}