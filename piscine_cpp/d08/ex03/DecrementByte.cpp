

#include "DecrementByte.hpp"

DecrementByte::DecrementByte()
{
}

DecrementByte::DecrementByte(DecrementByte &)
{
}

DecrementByte::~DecrementByte()
{
}

DecrementByte	&DecrementByte::operator=(DecrementByte &)
{
	return *this;
}

void		DecrementByte::execute(ExecutionHandler &exec)
{
	unsigned char	*data_ptr;

	data_ptr = *(exec.getEnviron().getDataPointer());
	if (*data_ptr == 0)
		(*data_ptr) = UCHAR_MAX;
	else
		(*data_ptr)--;
}