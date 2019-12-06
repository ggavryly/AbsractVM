#pragma once
#include "Parser.hpp"

enum Presicion
{
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double
};

class AVM
{
	friend Parser;
public:
	AVM(int argc, char **argv);
	
	AVM(AVM const &);
	
	~AVM();

public:
	void Parse();
	void Execute();
	void Exit(int exit_code);
	
private:
	std::list<Command>	_commands;
	int					_argc;
	char				**_argv;
};

