

#ifndef LOOPSTART_H
# define LOOPSTART_H

#include "IInstruction.hpp"

class LoopStart : public IInstruction
{
	public:
		LoopStart();
		LoopStart(LoopStart &other);
		virtual ~LoopStart();

		LoopStart	&operator=(LoopStart &other);
		void		execute(ExecutionHandler &exec);
};

#endif