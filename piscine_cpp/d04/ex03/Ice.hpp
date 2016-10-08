

#ifndef ICE_H
# define ICE_H

#include "AMateria.hpp"

class Ice : public AMateria
{
	public:
		Ice();
		Ice(Ice &other);
		virtual ~Ice();

		Ice			&operator=(Ice &other);
		AMateria	*clone() const;
		void		use(ICharacter& target);
};

#endif