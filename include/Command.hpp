#pragma once
#include <iostream>
#include "IOperand.hpp"
class Command
{
public:
	explicit Command(std::string const &&);
	Command();
	Command(Command const &);
	~Command();
	
public:
	const std::string &GetValue() const;
	void SetValue(const std::string &value);
	const std::string &GetAction() const;
	void SetAction(const std::string &action);
	Type GetType() const;
	void SetType(const std::string &type);

private:
	std::string _value = "$";
	std::string _action = "";
	Type		_type = ErrorType;
};

