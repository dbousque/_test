

#include "Squad.hpp"

Squad::Squad() :
	_len(0),
	_size(16),
	_marines(new ISpaceMarine*[16])
{
}

Squad::Squad(Squad &other)
{
	if (other.getCount() == 0)
	{
		this->_len = 0;
		this->_size = 16;
		this->_marines = new ISpaceMarine*[16];
	}
	else
	{
		this->_len = other.getCount();
		this->_size = other.getCount();
		this->_marines = new ISpaceMarine*[other.getCount()];
		for (int i = 0; i < other.getCount(); i++)
			this->_marines[i] = other.getUnit(i)->clone();
	}
}

Squad::~Squad()
{
	for (int i = 0; i < this->_len; i++)
		delete this->_marines[i];
	delete [] this->_marines;
}

Squad			&Squad::operator=(Squad &other)
{
	if (this->_len != 0)
	{
		for (int i = 0; i < this->_len; i++)
			delete this->_marines[i];
		delete [] this->_marines;
	}
	if (other.getCount() == 0)
	{
		this->_len = 0;
		this->_size = 16;
		this->_marines = new ISpaceMarine*[16];
	}
	else
	{
		this->_len = other.getCount();
		this->_size = other.getCount();
		this->_marines = new ISpaceMarine*[other.getCount()];
		for (int i = 0; i < other.getCount(); i++)
			this->_marines[i] = other.getUnit(i)->clone();
	}
	return *this;
}

int				Squad::getCount() const
{
	return this->_len;
}

ISpaceMarine*	Squad::getUnit(int n) const
{
	if (n < 0 || n >= this->_len)
		return (NULL);
	return this->_marines[n];
}

int				Squad::push(ISpaceMarine* space_marine)
{
	if (!space_marine)
		return this->_len;
	for (int i = 0; i < this->_len; i++)
	{
		if (this->_marines[i] == space_marine)
			return this->_len;
	}
	if (this->_len == this->_size)
	{
		this->_size *=2 ;
		ISpaceMarine	**new_elts = new ISpaceMarine*[this->_size];
		for (int i = 0; i < this->_len; i++)
			new_elts[i] = this->_marines[i];
		delete [] this->_marines;
		this->_marines = new_elts;
	}
	this->_marines[this->_len] = space_marine;
	this->_len++;
	return this->_len;
}