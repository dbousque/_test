

#include "Increment.hpp"

Increment::Increment()
{
}

Increment::Increment(Increment &)
{
}

Increment::~Increment()
{
}

Increment	&Increment::operator=(Increment &)
{
	return *this;
}

void		Increment::execute(ExecutionHandler &exec)
{
	unsigned char	**data_ptr;
	unsigned char	*data_start;

	data_ptr = exec.getEnviron().getDataPointer();
	data_start = exec.getEnviron().getDataStart();
	if (*data_ptr == data_start + exec.getEnviron().getN() - 1)
		*data_ptr = data_start;
	else
		(*data_ptr)++;
}