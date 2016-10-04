

#include "Pony.hpp"

void	ponyOnTheHeap(void)
{
	Pony			*pony1;
	std::string		name = "Gégé";

	pony1 = new Pony(39, 124, name);
	pony1->displayDescr();
	pony1->neigh();
	delete pony1;
}

void	ponyOnTheStack(void)
{
	std::string		name = "Didier";
	Pony			pony2 = Pony(26, 95, name);

	pony2.displayDescr();
	pony2.neigh();
}

int		main(void)
{
	std::cout << std::endl << "  Calling ponyOnTheHeap..." << std::endl << std::endl;
	ponyOnTheHeap();
	std::cout << std::endl << "  ... done." << std::endl;
	std::cout << "  Calling ponyOnTheStack..." << std::endl << std::endl;
	ponyOnTheStack();
	std::cout << std::endl << "  ... done." << std::endl;
	return (0);
}