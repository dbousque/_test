

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed(void) :
	_val(0)
{
}

Fixed::~Fixed()
{
}

Fixed::Fixed(Fixed const &other) :
	_val(other.getRawBits())
{
}

Fixed::Fixed(int const n) :
	_val(n << Fixed::_fractional_bits)
{
}

Fixed::Fixed(float const n) :
	_val(roundf(n * pow(2, Fixed::_fractional_bits)))
{
}

Fixed	&Fixed::operator=(Fixed const &other)
{
	this->_val = other.getRawBits();
	return *this;
}

bool	Fixed::operator>(Fixed const &other) const
{
	return this->_val > other.getRawBits();
}

bool	Fixed::operator<(Fixed const &other) const
{
	return this->_val < other.getRawBits();
}

bool	Fixed::operator>=(Fixed const &other) const
{
	return this->_val >= other.getRawBits();
}

bool	Fixed::operator<=(Fixed const &other) const
{
	return this->_val <= other.getRawBits();
}

bool	Fixed::operator==(Fixed const &other) const
{
	return this->_val == other.getRawBits();
}

bool	Fixed::operator!=(Fixed const &other) const
{
	return this->_val != other.getRawBits();
}

Fixed	Fixed::operator+(Fixed const &other) const
{
	Fixed	res;

	res.setRawBits(this->_val + other.getRawBits());
	return res;
}

Fixed	Fixed::operator-(Fixed const &other) const
{
	Fixed	res;

	res.setRawBits(this->_val - other.getRawBits());
	return res;
}

Fixed	Fixed::operator*(Fixed const &other) const
{
	Fixed	res;

	res.setRawBits((this->_val * other.getRawBits()) >> Fixed::_fractional_bits);
	return res;
}

Fixed	Fixed::operator/(Fixed const &other) const
{
	Fixed	res;

	res.setRawBits(((this->_val << Fixed::_fractional_bits) / other.getRawBits()));
	return res;
}

Fixed	&Fixed::operator++()
{
	this->_val++;
	return *this;
}

Fixed	Fixed::operator++(int)
{
	Fixed	res;

	res.setRawBits(this->_val);
	this->_val++;
	return res;
}

Fixed	&Fixed::operator--()
{
	this->_val--;
	return *this;
}

Fixed	Fixed::operator--(int)
{
	Fixed	res;

	res.setRawBits(this->_val);
	this->_val--;
	return res;
}


int		Fixed::getRawBits(void) const
{
	return this->_val;
}

void	Fixed::setRawBits(int const raw)
{
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

Fixed			&Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f2 < f1)
		return (f2);
	return (f1);
}

Fixed const		&Fixed::min(Fixed const &f1, Fixed const &f2)
{
	if (f2 < f1)
		return (f2);
	return (f1);
}

Fixed			&Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f2 > f1)
		return (f2);
	return (f1);
}

Fixed const		&Fixed::max(Fixed const &f1, Fixed const &f2)
{
	if (f2 > f1)
		return (f2);
	return (f1);
}

int const	Fixed::_fractional_bits = 8;