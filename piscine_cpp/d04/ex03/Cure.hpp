

#ifndef CURE_H
# define CURE_H

#include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		Cure();
		Cure(Cure &other);
		virtual ~Cure();

		Cure		&operator=(Cure &other);
		AMateria	*clone() const;
		void		use(ICharacter& target);
};

#endif