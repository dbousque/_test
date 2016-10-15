

#include "ExecutionHandler.hpp"
#include "Environment.hpp"
#include "IInstruction.hpp"
#include "IncrementByte.hpp"
#include "OutputByte.hpp"
#include "LoopStart.hpp"
#include "DecrementByte.hpp"
#include "LoopEnd.hpp"
#include "Decrement.hpp"
#include "Increment.hpp"
#include "AcceptByte.hpp"
#include "MindopenParser.hpp"
#include <vector>
#include <iostream>

void	test2()
{
	std::cout << "test 2, with two nested loops" << std::endl;
	Environment					env;
	std::vector<IInstruction*>	instructions;
	for (int i = 0; i < 42; i++)
		instructions.push_back(new IncrementByte());
	instructions.push_back(new OutputByte());
	instructions.push_back(new Increment());
	instructions.push_back(new IncrementByte());
	instructions.push_back(new IncrementByte());
	instructions.push_back(new Increment());
	instructions.push_back(new IncrementByte());
	instructions.push_back(new IncrementByte());
	instructions.push_back(new LoopStart());
	instructions.push_back(new LoopStart());
	instructions.push_back(new OutputByte());
	instructions.push_back(new DecrementByte());
	instructions.push_back(new LoopEnd());
	instructions.push_back(new Decrement());
	instructions.push_back(new LoopEnd());
	ExecutionHandler			exec(instructions, env);

	exec.launch();

	std::cout << std::endl;
}

void	test1()
{
	std::cout << "test 1, waiting for input, setting carater at current pointer, and decrementing until 0" << std::endl;
	std::vector<IInstruction*>	instructions;
	Environment					env;

	instructions.push_back(new AcceptByte());
	instructions.push_back(new LoopStart());
	instructions.push_back(new OutputByte());
	instructions.push_back(new DecrementByte());
	instructions.push_back(new LoopEnd());

	ExecutionHandler			exec(instructions, env);

	exec.launch();

	std::cout << std::endl;
}

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		test1();
		test2();
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			ExecutionHandler	exec(*(MindopenParser(argv[i]).parse()), *(new Environment()));
			exec.launch();
			std::cout << std::endl;
		}
	}
	return (0);
}

//+...+.>+>+[[-]<]