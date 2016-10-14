

#ifndef LOOPEND_H
# define LOOPEND_H

#include "IInstruction.hpp"

class LoopEnd : public IInstruction
{
	public:
		LoopEnd();
		LoopEnd(LoopEnd &other);
		virtual ~LoopEnd();

		LoopEnd		&operator=(LoopEnd &other);
		void		execute(ExecutionHandler &exec);
};

#endif