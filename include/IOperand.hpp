#pragma once
#include "main.hpp"

enum Type
{
	ErrorType = -1,
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand {
public:
	virtual int GetPrecision( void ) const = 0; // Precision of the type of the instance
	virtual Type GetType( void ) const = 0; // Type of the instance
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual std::string const & ToString( void ) const = 0; // String representation of the instance
	virtual ~IOperand( void ) {}
};

