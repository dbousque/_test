

#include "span.hpp"

Span::Span() :
	_n(0)
{
}

Span::Span(unsigned int n) :
	_n(n)
{
	this->_vals.reserve(n);
}

Span::Span(Span const &other) :
	_vals(other.getVals()),
	_n(other.getN())
{
}

Span::~Span()
{
}

Span	&Span::operator=(Span &other)
{
	this->_vals = other.getVals();
	this->_n = other.getN();
	return *this;
}

void	Span::addNumber(int x)
{
	if (this->_vals.size() >= this->_n)
		throw std::exception();
	this->_vals.push_back(x);
}

int		Span::shortestSpan()
{
	if (this->_vals.size() <= 1)
		throw std::exception();
	std::sort(this->_vals.begin(), this->_vals.end());
	int		shortest = this->_vals[1] - this->_vals[0];
	for (std::vector<int>::iterator iter = this->_vals.begin() + 1; iter != this->_vals.end() - 1; iter++)
	{
		if (*(iter + 1) - *iter < shortest)
			shortest = *(iter + 1) - *iter;
	}
	return shortest;
}

int		Span::longestSpan()
{
	if (this->_vals.size() <= 1)
		throw std::exception();
	std::sort(this->_vals.begin(), this->_vals.end());
	return this->_vals[this->_vals.size() - 1] - this->_vals[0];
}

std::vector<int> const	&Span::getVals() const
{
	return static_cast<std::vector<int> const &>(this->_vals);
}

unsigned int		Span::getN() const
{
	return this->_n;
}