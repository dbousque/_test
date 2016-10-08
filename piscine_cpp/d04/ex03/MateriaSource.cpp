

#include "MateriaSource.hpp"

MateriaSource::MateriaSource() :
	_materias(new AMateria*[4]),
	_names(new std::string[4]),
	_ind(0)
{
}

MateriaSource::MateriaSource(MateriaSource &other) :
	_materias(other.getMaterias()),
	_names(other.getNames()),
	_ind(other.getInd())
{
}

MateriaSource::~MateriaSource()
{
	delete [] this->_materias;
	delete [] this->_names;
}

MateriaSource	&MateriaSource::operator=(MateriaSource &other)
{
	this->_materias = other.getMaterias();
	this->_names = other.getNames();
	this->_ind = other.getInd();
	return *this;
}

void			MateriaSource::learnMateria(AMateria* materia)
{
	if (this->_ind < 4)
	{
		this->_materias[this->_ind] = materia->clone();
		this->_names[this->_ind] = materia->getType();
		this->_ind++;
	}
}

AMateria		*MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < this->_ind; i++)
	{
		if (type == this->_names[i])
			return this->_materias[i]->clone();
	}
	return (0);
}

int				MateriaSource::getInd()
{
	return this->_ind;
}

std::string		*MateriaSource::getNames()
{
	return this->_names;
}

AMateria		**MateriaSource::getMaterias()
{
	return this->_materias;
}