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

void	CheckType(const IOperand *&lhs, const IOperand *&rhs)
{
	int	maxPrecision = std::max(lhs->GetPrecision(), rhs->GetPrecision());
	if (lhs->GetPrecision() < maxPrecision)
	{
		IOperand const	*tmp = AVM::CreateOperand(static_cast<Type>(maxPrecision), lhs->ToString());
		delete lhs;
		lhs = tmp;
	}
	if (rhs->GetPrecision() < maxPrecision)
	{
		IOperand const	*tmp = AVM::CreateOperand(static_cast<Type>(maxPrecision), rhs->ToString());
		delete rhs;
		rhs = tmp;
	}
}

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

IOperand const* AVM::CreateOperand(Type const &type, std::string const &value)
{
	return _operand_factory[static_cast<Type>(0)](value);
}

IOperand const* AVM::CreateInt8(std::string const &value)
{
	return new Operand<int8_t>(value, static_cast<Type>(0));
}

IOperand const* AVM::CreateInt16(std::string const &value)
{
	return new Operand<int16_t>(value, static_cast<Type>(1));
}

IOperand const* AVM::CreateInt32(std::string const &value)
{
	return new Operand<int32_t>(value, static_cast<Type>(2));
}

IOperand const* AVM::CreateFloat(std::string const &value)
{
	return new Operand<float>(value, static_cast<Type>(3));
}

IOperand const* AVM::CreateDouble(std::string const &value)
{
	return new Operand<double>(value, static_cast<Type>(4));
}

void AVM::Push(std::string const &value, Type type)
{
	_stack.push_back(CreateOperand(type, value));
}

void AVM::Assert(std::string const &value, Type type)
{
	if (!_stack.empty())
	{
		auto *ptr = AVM::CreateOperand(type, value);
		if (_stack.back()->GetType() == type && _stack.back()->ToString() == value)
			std::cout << "Yeah, Great assert!" << std::endl;
		else
		{
			std::cerr << "No!, assert crush" << std::endl;
			AVM::Exit();
		}
		delete ptr;
	}
	else
		throw AVM::StackIsEmpty();
}

void AVM::Pop()
{
	if (_stack.empty())
		throw AVM::StackIsEmpty();
	_stack.pop_back();
}

void AVM::Dump()
{
	if (_stack.empty())
		std::cout << "Stack is empty" << std::endl;
	else
	{
		for (auto elem = _stack.rend(), end = _stack.rbegin(); elem != end; elem++)
			std::cout << (*elem)->ToString() << std::endl;
	}
}

void AVM::Print()
{
	if (_stack.empty())
	{
		std::cout << "Stack is empty" << std::endl;
		AVM::Exit();
	}
	else
	{
		if (!_stack.back()->GetPrecision())
			std::cout << std::stoi(_stack.back()->ToString().c_str()) << std::endl;
		else
			std::cerr << "Print assert failed!" << std::endl;
	}
}

void AVM::Add()
{
	if (_stack.size() > 1)
	{
		IOperand const	*right = _stack.back();
		_stack.pop_back();
		IOperand const	*left = _stack.back();
		_stack.pop_back();
		CheckType(left, right);
		_stack.push_back(left + right);
		delete right;
		delete left;
	}
	else
		throw AVM::NotEnoughData();
}

void AVM::Exit()
{
	std::cout << "Stop executing the program" << std::endl;
	exit(1);
}

const char* AVM::StackIsEmpty::what() const noexcept
{
	return "Error: stack is empty";
}

const char* AVM::NotEnoughData::what() const noexcept
{
	return "Not enough data for action";
}

const char* AVM::IncorrectType::what() const noexcept
{
	return "Wrong type";
}
