

#include "LoopEnd.hpp"
#include "LoopStart.hpp"

LoopEnd::LoopEnd()
{
}

LoopEnd::LoopEnd(LoopEnd &)
{
}

LoopEnd::~LoopEnd()
{
}

LoopEnd	&LoopEnd::operator=(LoopEnd &)
{
	return *this;
}

void		LoopEnd::execute(ExecutionHandler &exec)
{
	unsigned char	*data_ptr;
	size_t			nb_open;
	size_t			instr_pointer;

	data_ptr = *(exec.getEnviron().getDataPointer());
	if (*data_ptr != 0)
	{
		nb_open = -1;
		instr_pointer = exec.getInstructionPointer();
		exec.decrInstructionPointer();
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
			exec.decrInstructionPointer();
		}
	}
}