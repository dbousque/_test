

#ifndef DECREMENTBYTE_H
# define DECREMENTBYTE_H

#include "IInstruction.hpp"

class DecrementByte : public IInstruction
{
	public:
		DecrementByte();
		DecrementByte(DecrementByte &other);
		virtual ~DecrementByte();

		DecrementByte	&operator=(DecrementByte &other);
		void		execute(Environment &env);
}

#endif