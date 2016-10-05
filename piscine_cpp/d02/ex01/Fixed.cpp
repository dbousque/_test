

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed(void) :
	_val(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(Fixed const &other) :
	_val(other.getRawBits())
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::Fixed(int const n) :
	_val(n << Fixed::_fractional_bits)
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(float const n) :
	_val(roundf(n * pow(2, Fixed::_fractional_bits)))
{
	std::cout << "Float constructor called" << std::endl;
}

Fixed	&Fixed::operator=(Fixed const &other)
{
	std::cout << "Assignation operator called" << std::endl;
	this->_val = other.getRawBits();
	return *this;
}

int		Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->_val;
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->_val = raw;
}

float	Fixed::toFloat(void) const
{
	float	res;

	res = this->_val;
	return res / pow(2, Fixed::_fractional_bits);
}

int		Fixed::toInt(void) const
{
	return this->_val >> Fixed::_fractional_bits;
}

std::ostream	&operator<<(std::ostream &os, Fixed const &fix)
{
	os << fix.toFloat();
	return os;
}

int const	Fixed::_fractional_bits = 8;