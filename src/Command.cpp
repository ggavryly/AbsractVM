#include "Command.hpp"

Command::Command(std::string const && action) : _action(action)
{}

Command::Command()
{}

Command::Command(Command const &e)
{
	this->_action = e.GetAction();
	this->_value = e.GetValue();
}

Command::~Command()
{}

const std::string &Command::GetValue() const
{
	return _value;
}

void Command::SetValue(const std::string &value)
{
	_value = value;
}

const std::string &Command::GetAction() const
{
	return _action;
}

void Command::SetAction(const std::string &action)
{
	_action = action;
}

Type Command::GetType() const
{
	return _type;
}

void Command::SetType(const std::string &type)
{
	if (type == "int8")
		_type = static_cast<Type>(0);
	else if (type == "int16")
		_type = static_cast<Type>(1);
	else if (type == "int32")
		_type = static_cast<Type>(2);
	else if (type == "float")
		_type = static_cast<Type>(3);
	else if (type == "double")
		_type = static_cast<Type>(4);
}
