#pragma once
#include "Parser.hpp"
#include "Operand.hpp"
#include "OperandFactory.hpp"
class AVM
{
public:
	AVM(int argc, char **argv);
	AVM(AVM const &);
	~AVM();

private:
	IOperand const * CreateOperand(Type const & type, std::string const & value) const;
	IOperand const * CreateInt8(std::string const & value) const;
	IOperand const * CreateInt16(std::string const & value) const;
	IOperand const * CreateInt32(std::string const & value) const;
	IOperand const * CreateFloat(std::string const & value) const;
	IOperand const * CreateDouble(std::string const & value) const;
	
public:
	void Parse();
	void Execute();
	void Exit();
	void Push(std::string const & value, Type type);
	void Pop();
	void Dump();
	void Assert(std::string const & value, Type type);
	void Add();
	void Sub();
	void Mul();
	void Div();
	void Mod();
	void Print();
	
private:
	std::list<Command>		_commands;
	std::vector<IOperand *>	_stack;
	OperandFactory			_factory;
	std::vector<IOperand const*(AVM::*)(std::string const &)>					_operand_factory;
	std::map<std::string, void (AVM::*)(void)>									_func_without_args;
	std::map<std::string, void (AVM::*)(std::string const &, Type)>				_func_with_args;
	int						_argc;
	char					**_argv;
};

