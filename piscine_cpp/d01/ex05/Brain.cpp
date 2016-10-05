

#include "Brain.hpp"

Brain::Brain(int iq, int weight, long nb_neurons) :
	_iq(iq),
	_weight(weight),
	_nb_neurons(nb_neurons)
{
}

Brain::Brain() :
	_iq(112),
	_weight(2300),
	_nb_neurons(1)
{
}

Brain::~Brain()
{
}

int const	&Brain::getIq(void) const
{
	return this->_iq;
}
int const	&Brain::getWeight(void) const
{
	return this->_weight;
}
long		Brain::getNbNeurons(void) const
{
	return this->_nb_neurons;
}

std::string	Brain::identify(void) const
{
	std::ostringstream	out;

	out << "0x" << this;
	return out.str();
}