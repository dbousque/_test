

#include "Ice.hpp"

std::string const	ice_name = "ice";

Ice::Ice() : AMateria(ice_name)
{
}

Ice::Ice(Ice &other) : AMateria(other)
{
}

Ice::~Ice()
{
}

Ice		&Ice::operator=(Ice &other)
{
	return *(new Ice(other));
}

AMateria	*Ice::clone() const
{
	return new Ice;
}

void	Ice::use(ICharacter& target)
{
	AMateria::use(target);
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}