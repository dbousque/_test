

#include "ExecutionHandler.hpp"
#include "Environment.hpp"
#include "IInstruction.hpp"
#include "IncrementByte.hpp"
#include "OutputByte.hpp"
#include <queue>

int		main(void)
{
	Environment					env;
	std::queue<IInstruction*>	instructions;
	for (int i = 0; i < 42; i++)
		instructions.push(new IncrementByte());
	instructions.push(new OutputByte());
	ExecutionHandler			exec(instructions, env);

	exec.launch();
	return (0);
}