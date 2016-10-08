

#include "AMateria.hpp"

std::string const	default_type = "default_type";

AMateria::AMateria() :
	_type(default_type)
{
}

AMateria::AMateria(std::string const & type) :
	_type(type),
	xp_(0)
{
}

AMateria::AMateria(AMateria &other) :
	_type(other.getType()),
	xp_(other.getXP())
{
}

AMateria::~AMateria()
{
}

AMateria			&AMateria::operator=(AMateria &other)
{
	return other;
}

std::string const	&AMateria::getType() const
{
	return this->_type;
}

unsigned int		AMateria::getXP() const
{
	return this->xp_;
}

void		AMateria::use(ICharacter& target)
{
	(void)target;
	this->xp_ += 10;
}