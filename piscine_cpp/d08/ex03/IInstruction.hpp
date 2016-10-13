

#ifndef IINSTRUCTION_H
# define IINSTRUCTION_H

#include "Environment.hpp"

class IInstruction
{
	virtual void	execute(Environment &env) = 0;
}

#endif