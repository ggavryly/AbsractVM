#pragma once
#include "main.hpp"
#include "IOperand.hpp"

template <typename T>
class Operand : IOperand
{
public:
	Operand(std::string const & value, Type precision);
	virtual ~Operand();
	
	int         GetPrecision() const override;
	Type        GetType() const override;
	std::string const &  ToString() const override;
	IOperand const *    operator+   (IOperand const &) const override;
	IOperand const *    operator-   (IOperand const &) const override;
	IOperand const *    operator*   (IOperand const &) const override;
	IOperand const *    operator/   (IOperand const &) const override;
	IOperand const *    operator%   (IOperand const &) const override;

private:
	class UnderflowError : public std::exception
	{
		const char* what() const noexcept;
	};
	class OverflowError : public std::exception
	{
		const char* what() const noexcept;
	};
	class DivisionByZeroError : public std::exception
	{
		const char* what() const noexcept;
	};
	class ModuloByZeroError : public std::exception
	{
		const char* what() const noexcept;
	};
	
private:
	T			_value;
	Type		_precision;
	std::string	_str_value;
};

