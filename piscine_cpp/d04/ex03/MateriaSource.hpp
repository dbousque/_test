

#ifndef MATERIASOURCE_H
# define MATERIASOURCE_H

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	public:
		MateriaSource();
		MateriaSource(MateriaSource &other);
		virtual ~MateriaSource();

		MateriaSource	&operator=(MateriaSource &other);
		void			learnMateria(AMateria*);
		AMateria		*createMateria(std::string const &type);
		int				getInd();
		std::string		*getNames();
		AMateria		**getMaterias();

	private:
		AMateria	**_materias;
		std::string	*_names;
		int			_ind;
};

#endif