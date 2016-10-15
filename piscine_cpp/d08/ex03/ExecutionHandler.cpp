

#include "ExecutionHandler.hpp"
#include "IInstruction.hpp"

ExecutionHandler::ExecutionHandler(std::vector<IInstruction*> &instructions, Environment &environ) :
	_instructions(instructions),
	_instruction_pointer(0),
	_environ(environ)
{
}

ExecutionHandler::ExecutionHandler(ExecutionHandler const &other) :
	_instructions(other.getInstructions()),
	_instruction_pointer(0),
	_environ(other.getEnviron())
{
}

ExecutionHandler::~ExecutionHandler()
{
}

ExecutionHandler	&ExecutionHandler::operator=(ExecutionHandler &other)
{
	return *(new ExecutionHandler(other));
}

void		ExecutionHandler::launch()
{
	while (this->_instruction_pointer < this->_instructions.size())
	{
		IInstruction *instr = this->_instructions[this->_instruction_pointer];
		instr->execute(*this);
		this->_instruction_pointer++;
	}
}

void		ExecutionHandler::decrInstructionPointer()
{
	if (this->_instruction_pointer > 0)
		this->_instruction_pointer--;
}

void		ExecutionHandler::incrInstructionPointer()
{
	if (this->_instruction_pointer < this->_instructions.size() - 1)
		this->_instruction_pointer++;
}

std::vector<IInstruction*>	&ExecutionHandler::getInstructions() const
{
	return this->_instructions;
}

Environment		&ExecutionHandler::getEnviron() const
{
	return this->_environ;
}

size_t			ExecutionHandler::getInstructionPointer() const
{
	return this->_instruction_pointer;
}

IInstruction	*ExecutionHandler::getCurrentInstruction() const
{
	return this->_instructions[this->_instruction_pointer];
}