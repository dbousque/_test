

#ifndef EXECUTIONHANDLER_H
# define EXECUTIONHANDLER_H

#include <queue>
#include "Environment.hpp"

class IInstruction;

class ExecutionHandler
{
	public:
		ExecutionHandler(std::queue<IInstruction*> &instructions, Environment &eviron);
		ExecutionHandler(ExecutionHandler const &other);
		virtual ~ExecutionHandler();

		ExecutionHandler			&operator=(ExecutionHandler &other);
		void						launch();
		std::queue<IInstruction*>	&getInstructions() const;
		std::queue<IInstruction*>	&getPassedInstructions() const;
		Environment					&getEnviron() const;

	private:
		ExecutionHandler();
		
		std::queue<IInstruction*>	&_instructions;
		std::queue<IInstruction*>	_passed_instructions;
		Environment					&_environ;
};

#endif