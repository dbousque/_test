

#include "ExecutionHandler.hpp"
#include "IInstruction.hpp"

ExecutionHandler::ExecutionHandler(std::queue<IInstruction*> &instructions, Environment &environ) :
	_instructions(instructions),
	_environ(environ)
{
}

ExecutionHandler::ExecutionHandler(ExecutionHandler const &other) :
	_instructions(other.getInstructions()),
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

void				ExecutionHandler::launch()
{
	while (!this->_instructions.empty())
	{
		IInstruction &instr = *this->_instructions.front();
		instr.execute(*this);
		this->_instructions.pop();
		this->_passed_instructions.push(instr);
	}
}

std::queue<IInstruction*>	&ExecutionHandler::getInstructions() const
{
	return this->_instructions;
}

std::queue<IInstruction*>	&ExecutionHandler::getPassedInstructions() const
{
	return &(this->_passed_instructions);
}

Environment		&ExecutionHandler::getEnviron() const
{
	return this->_environ;
}