

#include "LoopStart.hpp"

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

	data_ptr = *(exec.getEnviron().getDataPointer());
	if (*data_ptr != 0)
	{
		ExecutionHandler	new_exec(exec.getPassedInstructions(), exec.getEnviron());
		new_exec.launch();
	}
}

>+>+>+>++++[[-]<].