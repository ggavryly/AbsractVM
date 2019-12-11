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

#include "AVM.hpp"

template <typename T>
const char* Operand<T>::UnderflowError::what() const noexcept
{
	return "Instruction attempt to store inside an variable a value that is larger than the minimum value";
}
template <typename T>
const char* Operand<T>::OverflowError::what() const noexcept
{
	return "Instruction attempt to store inside an variable a value that is larger than the maximum value";
}
template <typename T>
const char* Operand<T>::DivisionByZeroError::what() const noexcept
{
	return "Instruction attempt to divide value by zero";
}
template <typename T>
const char* Operand<T>::ModuloByZeroError::what() const noexcept
{
	return "Instruction attempt to modulo value by zero";
}

template<typename T>
Operand<T>::Operand(std::string const & value, Type precision) : _str_value(value) ,_precision(precision)
{
	std::stringstream string_value(value);
	long double tmp;
	string_value >> tmp;
	_value = tmp;
	if (tmp > std::numeric_limits<T>::max())
		throw Operand::OverflowError();
	if (tmp < std::numeric_limits<T>::lowest())
		throw Operand::UnderflowError();
}
template<typename T>
Operand<T>::~Operand()
{}
template<typename T>
Type Operand<T>::GetType() const
{
	return _precision;
}
template<typename T>
int Operand<T>::GetPrecision() const
{
	return static_cast<int>(_precision);
}
template <typename T>
std::string const & Operand<T>::ToString() const
{
	return _str_value;
}

template <typename T>
IOperand const* Operand<T>::operator+(IOperand const &rhs) const
{
	long double         r_arg;
	T                   tmp;
	std::stringstream   stream(rhs.ToString());
	
	stream >> r_arg;
	tmp = r_arg; tmp += _value;
	if (r_arg > 0 && _value > 0 && tmp < 0)
		throw Operand::OverflowError();
	if (r_arg < 0 && _value < 0 && tmp > 0)
		throw Operand::UnderflowError();
	return AVM::CreateOperand(_precision, std::to_string(static_cast<int64_t>(_value + r_arg)));
}
template <typename T>
IOperand const* Operand<T>::operator-(IOperand const &rhs) const
{
	long double         r_arg;
	T                   tmp;
	std::stringstream   stream(rhs.ToString());
	
	stream >> r_arg;
	tmp = _value; tmp -= r_arg;
	if (r_arg < 0 && _value > 0 && tmp < 0)
		throw Operand::OverflowError();
	if (r_arg > 0 && _value < 0 && tmp > 0)
		throw Operand::UnderflowError();
	return AVM::CreateOperand(_precision, std::to_string(static_cast<int64_t>(_value - r_arg)));
}
template <typename T>
IOperand const* Operand<T>::operator*(IOperand const &rhs) const
{
	long double         r_arg;
	T                   tmp;
	std::stringstream   stream(rhs.ToString());
	
	stream >> r_arg;
	tmp = r_arg; tmp *= _value;
	if ((r_arg < 0 && _value < 0 && tmp / r_arg != _value) || (r_arg > 0 && _value > 0 && tmp / r_arg != _value))
		throw Operand::OverflowError();
	if ((_value < 0 || r_arg < 0) && (tmp / r_arg != _value))
		throw Operand::UnderflowError();
	return AVM::CreateOperand(_precision, std::to_string(static_cast<int64_t>(_value * r_arg)));
}
template <typename T>
IOperand const* Operand<T>::operator/(IOperand const &rhs) const
{
	int64_t				r_arg;
	std::stringstream   stream(rhs.ToString());
	stream >> r_arg;
	
	if (r_arg == 0)
		throw Operand::DivisionByZeroError();
	return AVM::CreateOperand(_precision, std::to_string(static_cast<int64_t>(_value / r_arg)));
}
template <typename T>
IOperand const* Operand<T>::operator%(IOperand const &rhs) const
{
	int64_t r_arg;
	std::stringstream   stream(rhs.ToString());
	stream >> r_arg;
	
	if (r_arg == 0)
		throw Operand::ModuloByZeroError();
	return AVM::CreateOperand(_precision, std::to_string(static_cast<int64_t>(_value % r_arg)));
}
template<>
IOperand const* Operand<float>::operator%(IOperand const & rhs) const
{
	float   r_arg;
	std::stringstream   stream(rhs.ToString());
	stream >> r_arg;
	
	if (r_arg == 0.0f)
		throw Operand::ModuloByZeroError();
	return AVM::CreateOperand(static_cast<Type>(_precision), std::to_string(fmod(_value, r_arg)));
}
template<>
IOperand const* Operand<double>::operator%(IOperand const & rhs) const
{
	double   r_arg;
	std::stringstream  stream(rhs.ToString());
	stream >> r_arg;
	
	if (r_arg == 0.0)
		throw Operand::ModuloByZeroError();
	return AVM::CreateOperand(static_cast<Type>(_precision), std::to_string(fmod(_value, r_arg)));
}
template<>
IOperand const* Operand<float>::operator/(IOperand const & rhs) const
{
	float   r_arg, tmp;
	std::stringstream   stream(rhs.ToString());
	stream >> r_arg;
	
	if (r_arg == 0.0f)
		throw Operand::DivisionByZeroError();
	tmp = _value / r_arg;
	if (tmp == std::numeric_limits<float>::infinity())
		throw Operand::OverflowError();
	if (tmp == -std::numeric_limits<float>::infinity())
		throw Operand::UnderflowError();
	return AVM::CreateOperand(Type::Float, std::to_string(tmp));
}
template<>
IOperand const* Operand<double>::operator/(IOperand const & rhs) const
{
	double   r_arg, tmp;
	std::stringstream  stream(rhs.ToString());
	stream >> r_arg;
	
	if (r_arg == 0.0)
		throw Operand::DivisionByZeroError();
	tmp = _value / r_arg; stream << tmp;
	if (tmp == std::numeric_limits<double>::infinity())
		throw Operand::OverflowError();
	if (tmp == -std::numeric_limits<double>::infinity())
		throw Operand::UnderflowError();
	return AVM::CreateOperand(Type::Double, std::to_string(tmp));
}
template<>
IOperand const* Operand<float>::operator*(IOperand const & rhs) const
{
	float   r_arg, tmp;
	std::stringstream   stream(rhs.ToString());
	stream >> r_arg;
	
	tmp = _value * r_arg;
	if (tmp == std::numeric_limits<float>::infinity())
		throw Operand::OverflowError();
	if (tmp == -std::numeric_limits<float>::infinity())
		throw Operand::UnderflowError();
	return AVM::CreateOperand(Type::Float, std::to_string(tmp));
}
template<>
IOperand const* Operand<double>::operator*(IOperand const & rhs) const
{
	double   r_arg, tmp;
	std::stringstream  stream(rhs.ToString());
	stream >> r_arg;
	
	tmp = _value * r_arg;
	if (tmp == std::numeric_limits<double>::infinity())
		throw Operand::OverflowError();
	if (tmp == -std::numeric_limits<double>::infinity())
		throw Operand::UnderflowError();
	return AVM::CreateOperand(Type::Double, std::to_string(tmp));
}
