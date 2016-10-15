

#ifndef EXECUTIONHANDLER_H
# define EXECUTIONHANDLER_H

#include <vector>
#include "Environment.hpp"

class IInstruction;

class ExecutionHandler
{
	public:
		ExecutionHandler(std::vector<IInstruction*> &instructions, Environment &eviron);
		ExecutionHandler(ExecutionHandler const &other);
		virtual ~ExecutionHandler();

		ExecutionHandler			&operator=(ExecutionHandler &other);
		void						launch();
		void						decrInstructionPointer();
		void						incrInstructionPointer();
		std::vector<IInstruction*>	&getInstructions() const;
		Environment					&getEnviron() const;
		size_t						getInstructionPointer() const;
		IInstruction				*getCurrentInstruction() const;

	private:
		ExecutionHandler();
		
		std::vector<IInstruction*>	&_instructions;
		size_t						_instruction_pointer;
		Environment					&_environ;
};

#endif