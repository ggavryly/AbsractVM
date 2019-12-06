#pragma once
#include "main.hpp"
#include "Command.hpp"
class ErrorHandling
{
public:
	ErrorHandling();
	ErrorHandling(ErrorHandling const &);
	~ErrorHandling();
	
public:
	static bool ExitTest(std::list<Command> const &);

private:
	class NoExitCommand : public std::exception
	{
		const char* what() const noexcept;
	};

private:
};

