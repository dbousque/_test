

#ifndef DECREMENT_H
# define DECREMENT_H

#include "IInstruction.hpp"

class Decrement : public IInstruction
{
	public:
		Decrement();
		Decrement(Decrement &other);
		virtual ~Decrement();

		Decrement	&operator=(Decrement &other);
		void		execute(ExecutionHandler &exec);
};

#endif