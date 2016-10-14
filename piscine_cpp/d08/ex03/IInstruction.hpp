

#ifndef IINSTRUCTION_H
# define IINSTRUCTION_H

#include "ExecutionHandler.hpp"

class IInstruction
{
	public:
		virtual void	execute(ExecutionHandler &exec) = 0;
		virtual			~IInstruction() {}
};

#endif