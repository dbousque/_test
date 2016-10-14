

#include "IncrementByte.hpp"

IncrementByte::IncrementByte()
{
}

IncrementByte::IncrementByte(IncrementByte &)
{
}

IncrementByte::~IncrementByte()
{
}

IncrementByte	&IncrementByte::operator=(IncrementByte &)
{
	return *this;
}

void		IncrementByte::execute(ExecutionHandler &exec)
{
	unsigned char	*data_ptr;

	data_ptr = *(exec.getEnviron().getDataPointer());
	if (*data_ptr == UCHAR_MAX)
		(*data_ptr) = 0;
	else
		(*data_ptr)++;
}