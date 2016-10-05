

#ifndef BRAIN_H
# define BRAIN_H

#include <string>
#include <sstream>

class Brain
{
	public:
		Brain();
		Brain(int iq, int weight, long nb_neurons);
		~Brain();
		std::string	identify(void) const;
		int const	&getIq(void) const;
		int const	&getWeight(void) const;
		long		getNbNeurons(void) const;

	private:
		int const	_iq;
		int const	_weight;
		long 		_nb_neurons;
};

#endif