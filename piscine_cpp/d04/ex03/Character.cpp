

#include "Character.hpp"

Character::Character(std::string const &name) :
	_name(name),
	_materia_ind(0),
	_materias(new AMateria*[4])
{
}

Character::Character(Character &other) :
	_name(other.getName()),
	_materia_ind(other.getMateriInd()),
	_materias(new AMateria*[4])
{
	for (int i = 0; i < other.getMateriInd(); i++)
		this->_materias[i] = other.getMaterias()[i]->clone();
}

Character::~Character()
{
	for (int i = 0; i < this->_materia_ind; i++)
		delete this->_materias[i];
	delete [] this->_materias;
}

Character			&Character::operator=(Character &other)
{
	for (int i = 0; i < this->_materia_ind; i++)
		delete this->_materias[i];
	for (int i = 0; i < other.getMateriInd(); i++)
		this->_materias[i] = other.getMaterias()[i]->clone();
	this->_materia_ind = other.getMateriInd();
	return *this;
}

std::string const	&Character::getName() const
{
	return this->_name;
}

void				Character::equip(AMateria *m)
{
	if (this->_materia_ind < 4)
	{
		this->_materias[this->_materia_ind] = m;
		this->_materia_ind++;
	}
}

void				Character::unequip(int idx)
{
	if (this->_materia_ind > 0)
	{
		for (int i = idx; i < 3; i++)
			this->_materias[i] = this->_materias[i + 1];
		this->_materia_ind--;
	}
}

void				Character::use(int idx, ICharacter &target)
{
	if (idx >= 0 && idx < this->_materia_ind)
		this->_materias[idx]->use(target);
}

AMateria			**Character::getMaterias()
{
	return this->_materias;
}

int					Character::getMateriInd()
{
	return this->_materia_ind;
}
