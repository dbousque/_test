

#include "Float.hpp"

Float::Float(float value) : _value(value)
{
}

Float::Float(Float &other) : _value(other._value)
{
}

Float::~Float()
{
}


Float &Float::operator=(Float &other)
{
  this->_value = other.value;
  return *this;
}


int Float::getPrecision() const
{
  return FloatType;
}

eOperandType Float::getType() const
{
  return FloatType;
}

IOperand const *Float::operator+(IOperand const &rhs) const
{
  eOperandType  highestPrecision;

  highest = this->getPrecision() > rhs.getPrecision() ? this->getPrecision() : rhs.getPrecision;
  return createOperand(highestPrecision, )
}

IOperand const *Float::operator-(IOperand const &rhs) const
{

}

IOperand const *Float::operator*(IOperand const &rhs) const
{

}

IOperand const *Float::operator/(IOperand const &rhs) const
{

}

IOperand const *Float::operator%(IOperand const &rhs) const
{

}


std::string const &Float::toString() const
{

}
