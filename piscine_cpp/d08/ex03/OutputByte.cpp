

#include "OutputByte.hpp"

OutputByte::OutputByte()
{
}

OutputByte::OutputByte(OutputByte &)
{
}

OutputByte::~OutputByte()
{
}

OutputByte	&OutputByte::operator=(OutputByte &)
{
	return *this;
}

void		OutputByte::execute(ExecutionHandler &exec)
{
	unsigned char	*data_ptr;

	data_ptr = *(exec.getEnviron().getDataPointer());
	std::cout << *data_ptr;
}