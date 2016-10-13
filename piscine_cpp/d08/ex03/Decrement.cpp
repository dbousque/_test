

#include "Decrement.hpp"

Decrement::Decrement()
{
}

Decrement::Decrement(Decrement &other)
{
}

Decrement::~Decrement()
{
}

Decrement	&Decrement::operator=(Decrement &other)
{
}

void		Decrement::execute(Environment &env)
{
	unsigned char	*data_pointer;

	data_pointer = *(env.getDataPointer());
	if (data_pointer - env.getDataStart() >= env.getN())
		data_pointer = env.getDataStart();
	else
		data_pointer += 1;
}