

#include "DecrementByte.hpp"

DecrementByte::DecrementByte()
{
}

DecrementByte::DecrementByte(DecrementByte &other)
{
}

DecrementByte::~DecrementByte()
{
}

DecrementByte	&DecrementByte::operator=(DecrementByte &other)
{
}

void		DecrementByte::execute(Environment &env)
{
	unsigned char	*data_pointer;

	data_pointer = *(env.getDataPointer());
	if (data_pointer - env.getDataStart() >= env.getN())
		data_pointer = env.getDataStart();
	else
		data_pointer += 1;
}