

#include "TacticalMarine.hpp"

TacticalMarine::TacticalMarine()
{
	std::cout << "Tactical Marine ready for battle" << std::endl;
}

TacticalMarine::TacticalMarine(TacticalMarine &other)
{
	(void)other;
	std::cout << "Tactical Marine ready for battle" << std::endl;
}

TacticalMarine::~TacticalMarine()
{
	std::cout << "Aaargh ..." << std::endl;
}

TacticalMarine	&TacticalMarine::operator=(TacticalMarine &other)
{
	(void)other;
	return *this;
}

TacticalMarine*	TacticalMarine::clone() const
{
	return new TacticalMarine();
}

void			TacticalMarine::battleCry() const
{
	std::cout << "For the holy PLOT !”" << std::endl;
}

void			TacticalMarine::rangedAttack() const
{
	std::cout << "* attacks with bolter *" << std::endl;
}

void			TacticalMarine::meleeAttack() const
{
	std::cout << "* attacks with chainsword *" << std::endl;
}