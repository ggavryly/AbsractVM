#include <OperandFactory.hpp>
#include "Operand.hpp"
template <typename T>
const char* Operand<T>::UnderflowError::what() const noexcept
{
	return "This instruction attempt to store inside an variable a value that is larger than the maximum value";
}
template <typename T>
const char* Operand<T>::OverflowError::what() const noexcept
{
	return "This instruction attempt to store inside an variable a value that is larger than the minimum value";
}
template <typename T>
const char* Operand<T>::DivisionByZeroError::what() const noexcept
{
	return "This instruction attempt to divide value by zero";
}
template <typename T>
const char* Operand<T>::ModuloByZeroError::what() const noexcept
{
	return "This instruction attempt to modulo value by zero";
}
template<typename T>
Operand<T>::Operand(std::string const & value, Type precision) : _str_value(value), _precision(precision)
{
	std::stringstream string_value(value);
	string_value >> _value;
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
IOperand const* Operand<T>::operator+(IOperand const &r) const
{
	long double         rhs;
	T                   tmp;
	std::stringstream   stream(r.ToString());
	
	stream >> rhs;
	tmp = rhs; tmp += _value;
	if (rhs > 0 && _value > 0 && tmp < 0)
		throw Operand::OverflowError();
	if (rhs < 0 && _value < 0 && tmp > 0)
		throw Operand::UnderflowError();
}
template <typename T>
IOperand const* Operand<T>::operator-(IOperand const &r) const
{
	long double         rhs;
	T                   tmp;
	std::stringstream   stream(r.ToString());
	
	stream >> rhs;
	tmp = _value; tmp -= rhs;
	if (rhs < 0 && _value > 0 && tmp < 0)
		throw Operand::OverflowError();
	if (rhs > 0 && _value < 0 && tmp > 0)
		throw Operand::UnderflowError();
}
template <typename T>
IOperand const* Operand<T>::operator*(IOperand const &r) const
{
	long double         rhs;
	T                   tmp;
	std::stringstream   stream(r.ToString());
	
	stream >> rhs;
	tmp = rhs; tmp *= _value;
	if ((rhs < 0 && _value < 0 && tmp / rhs != _value) || (rhs > 0 && _value > 0 && tmp / rhs != _value))
		throw Operand::OverflowError();
	if ((_value < 0 || rhs < 0) && (tmp / rhs != _value))
		throw Operand::UnderflowError();
}
template <typename T>
IOperand const* Operand<T>::operator/(IOperand const &r) const
{
	int64_t rhs;  std::stringstream   stream(r.ToString());
	stream >> rhs;
	
	if (rhs == 0)
		throw Operand::DivisionByZeroError();
	
	return OperandFactory::CreateOperand(static_cast<Type>(_precision), std::to_string((int64_t)(_value / rhs)));
}
template <typename T>
IOperand const* Operand<T>::operator%(IOperand const &r) const
{

}
