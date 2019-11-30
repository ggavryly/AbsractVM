#pragma once
#include "main.hpp"
#include "IOperand.hpp"

class Operand : IOperand
{
public:
	Operand();
	
	Operand(Operand const &);
	
	~Operand();

private:
};

