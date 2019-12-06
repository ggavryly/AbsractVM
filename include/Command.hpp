#pragma once
#include <iostream>
class Command
{
public:
	Command(std::string const &&);
	Command();
	Command(Command const &);
	~Command();
	
public:
	const std::string &GetValue() const;
	void SetValue(const std::string &value);
	const std::string &GetAction() const;
	void SetAction(const std::string &action);

private:
	std::string _value = "$";
	std::string _action;
};

