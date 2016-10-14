

#ifndef ACCEPTBYTE_H
# define ACCEPTBYTE_H

#include "IInstruction.hpp"
#include <stdio.h>

class AcceptByte : public IInstruction
{
	public:
		AcceptByte();
		AcceptByte(AcceptByte &other);
		virtual ~AcceptByte();

		AcceptByte	&operator=(AcceptByte &other);
		void		execute(ExecutionHandler &exec);
};

#endif