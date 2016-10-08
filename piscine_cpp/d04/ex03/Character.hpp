

#ifndef CHARACTER_H
# define CHARACTER_H

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>

class Character : public ICharacter
{
	public:
		Character(std::string const &name);
		Character(Character &other);
		virtual ~Character();

		Character			&operator=(Character &other);
		std::string const	&getName() const;
		void				equip(AMateria *m);
		void				unequip(int idx);
		void				use(int idx, ICharacter &target);
		AMateria			**getMaterias();
		int					getMateriInd();

	private:
		Character();

		std::string const	&_name;
		int					_materia_ind;
		AMateria			**_materias;
};

#endif