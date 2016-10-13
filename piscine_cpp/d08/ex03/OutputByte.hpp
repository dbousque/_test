

#ifndef OUTPUTBYTE_H
# define OUTPUTBYTE_H

#include "IInstruction.hpp"

class OutputByte : public IInstruction
{
	public:
		OutputByte();
		OutputByte(OutputByte &other);
		virtual ~OutputByte();

		OutputByte	&operator=(OutputByte &other);
		void		execute(Environment &env);
}

#endif