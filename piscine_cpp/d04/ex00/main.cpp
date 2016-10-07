

#include "Peon.hpp"
#include "Sorcerer.hpp"
#include "Victim.hpp"
#include "Caval.hpp"

int main()
{
	Sorcerer robert("Robert", "the Magnificent");

	Victim jim("Jimmy");
	Peon joe("Joe");

	std::cout << robert << jim << joe;

	robert.polymorph(jim);
	robert.polymorph(joe);

	std::cout << std::endl << "Testing Caval class" << std::endl;
	Caval lol("ECTOPLASME");
	lol.getPolymorphed();
	robert.polymorph(lol);
	std::cout << lol;
	return 0;
}