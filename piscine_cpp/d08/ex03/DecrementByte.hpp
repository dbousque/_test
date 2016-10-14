

#ifndef DECREMENTBYTE_H
# define DECREMENTBYTE_H

#include "IInstruction.hpp"
#include <climits>

class DecrementByte : public IInstruction
{
	public:
		DecrementByte();
		DecrementByte(DecrementByte &other);
		virtual ~DecrementByte();

		DecrementByte	&operator=(DecrementByte &other);
		void		execute(ExecutionHandler &exec);
};

#endif