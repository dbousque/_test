

#include "AcceptByte.hpp"

AcceptByte::AcceptByte()
{
}

AcceptByte::AcceptByte(AcceptByte &other)
{
}

AcceptByte::~AcceptByte()
{
}

AcceptByte	&AcceptByte::operator=(AcceptByte &other)
{
}

void		AcceptByte::execute(Environment &env)
{
	unsigned char	*data_pointer;

	data_pointer = *(env.getDataPointer());
	if (data_pointer - env.getDataStart() >= env.getN())
		data_pointer = env.getDataStart();
	else
		data_pointer += 1;
}