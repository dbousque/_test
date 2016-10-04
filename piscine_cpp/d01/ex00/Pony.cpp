

#include "Pony.hpp"

Pony::Pony(int tail_length, int height, std::string &name) :
	_tail_length(tail_length),
	_height(height),
	_name(name)
{
	std::cout << "Pony instance with name \"" << name << "\" created at address " << this << std::endl;
}

Pony::~Pony()
{
	std::cout << "Pony instance with name \"" << this->_name << "\" deleted" << std::endl;
}

void	Pony::neigh(void) const
{
	std::cout << "Pony \"" << this->_name << "\" neighs !" << std::endl;
}

void	Pony::displayDescr(void) const
{
	std::cout << "Pony \"" << this->_name << "\" :" << std::endl;
	std::cout << "  tail length : " << _tail_length << " cm" << std::endl;
	std::cout << "  height      : " << _height << " cm" << std::endl;
}