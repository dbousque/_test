

#include "Decrement.hpp"

Decrement::Decrement()
{
}

Decrement::Decrement(Decrement &)
{
}

Decrement::~Decrement()
{
}

Decrement	&Decrement::operator=(Decrement &)
{
	return *this;
}

void		Decrement::execute(ExecutionHandler &exec)
{
	unsigned char	**data_ptr;
	unsigned char	*data_start;

	data_ptr = exec.getEnviron().getDataPointer();
	data_start = exec.getEnviron().getDataStart();
	if (*data_ptr == data_start)
		*data_ptr = data_start + exec.getEnviron().getN() - 1;
	else
		(*data_ptr)--;
}