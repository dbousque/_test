

#include "Squad.hpp"
#include "AssaultTerminator.hpp"
#include "TacticalMarine.hpp"

void	more_complete_test()
{
	std::cout << std::endl << "Starting a more complete test" << std::endl;
	Squad	mySquad;

	std::cout << "Adding 10 marines to squad" << std::endl;
	for (int i = 0; i < 10; i++)
		mySquad.push(new TacticalMarine);
	AssaultTerminator	*term = new AssaultTerminator;
	std::cout << "Adding same marine twice, expecting getCount() not to change after the first one" << std::endl;
	std::cout << "getCount() : " << mySquad.getCount() << std::endl;
	mySquad.push(term);
	std::cout << "getCount() : " << mySquad.getCount() << std::endl;
	mySquad.push(term);
	std::cout << "getCount() : " << mySquad.getCount() << std::endl;
	std::cout << "Copying the squad using copy constructor :" << std::endl;
	Squad	nsquad(mySquad);
}

int main()
{
	ISpaceMarine* bob = new TacticalMarine;
	ISpaceMarine* jim = new AssaultTerminator;

	ISquad* vlc = new Squad;
	vlc->push(bob);
	vlc->push(jim);
	for (int i = 0; i < vlc->getCount(); ++i)
	{
		ISpaceMarine* cur = vlc->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}
	delete vlc;

	more_complete_test();
	return 0;
}