

#ifndef HUMAN_H
# define HUMAN_H

#include "Brain.hpp"
#include <string>

class Human
{
	public:
		Human();
		~Human();
		std::string	identify(void) const;
		Brain const	&getBrain(void) const;

	private:
		Brain const	_brain;
};

#endif