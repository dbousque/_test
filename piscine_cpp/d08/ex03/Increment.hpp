

#ifndef INCREMENT_H
# define INCREMENT_H

#include "IInstruction.hpp"

class Increment : public IInstruction
{
	public:
		Increment();
		Increment(Increment &other);
		virtual ~Increment();

		Increment	&operator=(Increment &other);
		void		execute(Environment &env);
}

#endif