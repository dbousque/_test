

#include "AcceptByte.hpp"
#include "ExecutionHandler.hpp"

AcceptByte::AcceptByte()
{
}

AcceptByte::AcceptByte(AcceptByte &)
{
}

AcceptByte::~AcceptByte()
{
}

AcceptByte	&AcceptByte::operator=(AcceptByte &)
{
	return *this;
}

void		AcceptByte::execute(ExecutionHandler &exec)
{
	unsigned char	*data_ptr;
	int				c;

	data_ptr = *(exec.getEnviron().getDataPointer());
	c = getchar();
	*data_ptr = static_cast<unsigned char>(c);
}