

#ifndef INCREMENTBYTE_H
# define INCREMENTBYTE_H

#include "IInstruction.hpp"
#include <climits>

class IncrementByte : public IInstruction
{
	public:
		IncrementByte();
		IncrementByte(IncrementByte &other);
		virtual ~IncrementByte();

		IncrementByte	&operator=(IncrementByte &other);
		void			execute(ExecutionHandler &exec);
};

#endif