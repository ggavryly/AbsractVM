#pragma once
#include "Parser.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

class AVM
{
public:
	AVM(int argc, char **argv);
	AVM(AVM const &);
	~AVM();
	
	static IOperand const * CreateOperand(Type const & type, std::string const & value);
private:
	static IOperand const * CreateInt8(std::string const & value);
	static IOperand const * CreateInt16(std::string const & value);
	static IOperand const * CreateInt32(std::string const & value);
	static IOperand const * CreateFloat(std::string const & value);
	static IOperand const * CreateDouble(std::string const & value);
	
public:
	void CheckType(const IOperand *&lhs, const IOperand *&rhs);
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
	std::list<Command>													_commands;
	std::vector<IOperand const *>										_stack;
	static std::vector<IOperand const*(*)(std::string const & value)>	_operand_factory;
	std::map<std::string, void (AVM::*)(void)>							_func_without_args;
	std::map<std::string, void (AVM::*)(std::string const &, Type)>		_func_with_args;
	int						_argc;
	char					**_argv;

private:
	class StackIsEmpty : public std::exception
	{
		const char* what() const noexcept;
	};
	class NotEnoughData : public std::exception
	{
		const char* what() const noexcept;
	};
	class IncorrectType : public std::exception
	{
		const char* what() const noexcept;
	};
	
};
