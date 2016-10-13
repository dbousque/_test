

#include "OutputByte.hpp"

OutputByte::OutputByte()
{
}

OutputByte::OutputByte(OutputByte &other)
{
}

OutputByte::~OutputByte()
{
}

OutputByte	&OutputByte::operator=(OutputByte &other)
{
}

void		OutputByte::execute(Environment &env)
{
	unsigned char	*data_pointer;

	data_pointer = *(env.getDataPointer());
	if (data_pointer - env.getDataStart() >= env.getN())
		data_pointer = env.getDataStart();
	else
		data_pointer += 1;
}
}