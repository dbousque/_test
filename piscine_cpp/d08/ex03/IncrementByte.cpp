

#include "IncrementByte.hpp"

IncrementByte::IncrementByte()
{
}

IncrementByte::IncrementByte(IncrementByte &other)
{
}

IncrementByte::~IncrementByte()
{
}

IncrementByte	&IncrementByte::operator=(IncrementByte &other)
{
}

void		IncrementByte::execute(Environment &env)
{
	unsigned char	*data_pointer;

	data_pointer = *(env.getDataPointer());
	if (data_pointer - env.getDataStart() >= env.getN())
		data_pointer = env.getDataStart();
	else
		data_pointer += 1;
}