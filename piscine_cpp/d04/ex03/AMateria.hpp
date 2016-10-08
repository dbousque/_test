

#ifndef AMATERIA_H
# define AMATERIA_H

#include <string>
#include <iostream>
#include "ICharacter.hpp"

class AMateria
{
	private:
		AMateria();
		std::string const	&_type;
		unsigned int		xp_;
	
	public:
		AMateria(std::string const & type);
		AMateria(AMateria &other);
		virtual ~AMateria();

		AMateria	&operator=(AMateria &other);
		std::string const & getType() const; //Returns the materia type
		unsigned int getXP() const; //Returns the Materia's XP
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};

#endif