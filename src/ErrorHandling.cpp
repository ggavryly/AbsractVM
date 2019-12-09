#include "ErrorHandling.hpp"

ErrorHandling::ErrorHandling()
{}

ErrorHandling::ErrorHandling(ErrorHandling const &)
{}

ErrorHandling::~ErrorHandling()
{}

const char* ErrorHandling::NoExitCommand::what() const noexcept
{
	return "[Exit] command hasn't been found";
}

bool ErrorHandling::ExitTest(std::list<Command> const &actions)
{
	if ((actions.back().GetAction() == "exit"))
		return true;
	throw ErrorHandling::NoExitCommand();
}