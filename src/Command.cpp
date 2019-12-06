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
