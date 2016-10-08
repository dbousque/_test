

#include "Cure.hpp"

std::string const	cure_name = "cure";

Cure::Cure() : AMateria(cure_name)
{
}

Cure::Cure(Cure &other) : AMateria(other)
{
}

Cure::~Cure()
{
}

Cure	&Cure::operator=(Cure &other)
{
	return *(new Cure(other));
}

AMateria	*Cure::clone() const
{
	return new Cure;
}

void	Cure::use(ICharacter& target)
{
	AMateria::use(target);
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}