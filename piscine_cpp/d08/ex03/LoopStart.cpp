

#include "LoopStart.hpp"
#include "LoopEnd.hpp"

LoopStart::LoopStart()
{
}

LoopStart::LoopStart(LoopStart &)
{
}

LoopStart::~LoopStart()
{
}

LoopStart	&LoopStart::operator=(LoopStart &)
{
	return *this;
}

void		LoopStart::execute(ExecutionHandler &exec)
{
	unsigned char	*data_ptr;
	size_t			nb_open;
	size_t			instr_pointer;

	data_ptr = *(exec.getEnviron().getDataPointer());
	if (*data_ptr == 0)
	{
		nb_open = 1;
		instr_pointer = exec.getInstructionPointer();
		exec.incrInstructionPointer();
		while (instr_pointer != exec.getInstructionPointer())
		{
			instr_pointer = exec.getInstructionPointer();
			if (dynamic_cast<LoopEnd*>(exec.getCurrentInstruction()))
			{
				nb_open--;
				if (nb_open == 0)
					break ;
			}
			else if (dynamic_cast<LoopStart*>(exec.getCurrentInstruction()))
			{
				nb_open++;
				if (nb_open == 0)
					break ;
			}
			exec.incrInstructionPointer();
		}
	}
}