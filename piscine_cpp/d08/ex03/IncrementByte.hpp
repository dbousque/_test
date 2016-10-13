

#ifndef INCREMENTBYTE_H
# define INCREMENTBYTE_H

#include "IInstruction.hpp"

class IncrementByte : public IInstruction
{
	public:
		IncrementByte();
		IncrementByte(IncrementByte &other);
		virtual ~IncrementByte();

		IncrementByte	&operator=(IncrementByte &other);
		void		execute(Environment &env);
}

#endif