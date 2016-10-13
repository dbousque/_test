

#include "Increment.hpp"

Increment::Increment()
{
}

Increment::Increment(Increment &other)
{
}

Increment::~Increment()
{
}

Increment	&Increment::operator=(Increment &other)
{
}

void		Increment::execute(Environment &env)
{
	unsigned char	*data_pointer;

	data_pointer = *(env.getDataPointer());
	if (data_pointer - env.getDataStart() >= env.getN())
		data_pointer = env.getDataStart();
	else
		data_pointer += 1;
}