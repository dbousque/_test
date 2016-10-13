

#ifndef ACCEPTBYTE_H
# define ACCEPTBYTE_H

#include "IInstruction.hpp"

class AcceptByte : public IInstruction
{
	public:
		AcceptByte();
		AcceptByte(AcceptByte &other);
		virtual ~AcceptByte();

		AcceptByte	&operator=(AcceptByte &other);
		void		execute(Environment &env);
}

#endif