#pragma once
#include "main.hpp"
#include "IOperand.hpp"
#include "AVM.hpp"

template <typename T>
class Operand : public IOperand
{
public:
	Operand(std::string const & value, Type precision);
	Operand(Operand<T> const &) = default;
	~Operand() override;
	
	int         GetPrecision() const override;
	Type        GetType() const override;
	std::string const &  ToString() const override;
	IOperand const * operator + (IOperand const &) const override;
	IOperand const * operator - (IOperand const &) const override;
	IOperand const * operator * (IOperand const &) const override;
	IOperand const * operator / (IOperand const &) const override;
	IOperand const * operator % (IOperand const &) const override;

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

