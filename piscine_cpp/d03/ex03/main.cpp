

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"
#include <iostream>

void	test_fragtrap()
{
	std::cout << "Creating FragTrap with name Léo" << std::endl;
	FragTrap	&leo = *(new FragTrap("Léo"));
	std::cout << "Creating FragTrap with default constructor" << std::endl;
	FragTrap	&anonym = *(new FragTrap());

	std::cout << "calling displayInfos for both FragTraps : " << std::endl;
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "CALLING vaulthunter_dot_exe 3 times on leo : " << std::endl;
	leo.vaulthunter_dot_exe("anonym");
	leo.vaulthunter_dot_exe("anonym");
	leo.vaulthunter_dot_exe("anonym");
	std::cout << std::endl;

	std::cout << "CALLING vaulthunter_dot_exe 3 times on anonym : " << std::endl;
	anonym.vaulthunter_dot_exe("leo");
	anonym.vaulthunter_dot_exe("leo");
	anonym.vaulthunter_dot_exe("leo");
	std::cout << std::endl;

	std::cout << "calling displayInfos for both FragTraps : " << std::endl;
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling takeDamage(60) on both FragTraps and displaying them" << std::endl;
	leo.takeDamage(60);
	anonym.takeDamage(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling takeDamage(60) on both FragTraps and displaying them" << std::endl;
	leo.takeDamage(60);
	anonym.takeDamage(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling beRepaired(60) on both FragTraps and displaying them" << std::endl;
	leo.beRepaired(60);
	anonym.beRepaired(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling beRepaired(60) on both FragTraps and displaying them" << std::endl;
	leo.beRepaired(60);
	anonym.beRepaired(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	delete &leo;
	delete &anonym;
}

void	test_scavtrap()
{
	std::cout << "Creating ScavTrap with name Paul" << std::endl;
	ScavTrap	&leo = *(new ScavTrap("Paul"));
	std::cout << "Creating ScavTrap with default constructor" << std::endl;
	ScavTrap	&anonym = *(new ScavTrap());

	std::cout << "calling displayInfos for both ScavTraps : " << std::endl;
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "CALLING challengeNewcomer 3 times on Paul : " << std::endl;
	leo.challengeNewcomer();
	leo.challengeNewcomer();
	leo.challengeNewcomer();
	std::cout << std::endl;

	std::cout << "CALLING challengeNewcomer 3 times on anonym : " << std::endl;
	anonym.challengeNewcomer();
	anonym.challengeNewcomer();
	anonym.challengeNewcomer();
	std::cout << std::endl;

	std::cout << "calling displayInfos for both ScavTraps : " << std::endl;
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling takeDamage(60) on both ScavTraps and displaying them" << std::endl;
	leo.takeDamage(60);
	anonym.takeDamage(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling takeDamage(60) on both ScavTraps and displaying them" << std::endl;
	leo.takeDamage(60);
	anonym.takeDamage(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling beRepaired(60) on both ScavTraps and displaying them" << std::endl;
	leo.beRepaired(60);
	anonym.beRepaired(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	std::cout << "calling beRepaired(60) on both ScavTraps and displaying them" << std::endl;
	leo.beRepaired(60);
	anonym.beRepaired(60);
	leo.displayInfos();
	anonym.displayInfos();
	std::cout << std::endl;

	delete &leo;
	delete &anonym;
}

void	test_ninjatrap()
{
	std::cout << "Creating NinjaTrap with name Takeido" << std::endl;
	NinjaTrap	&ninja = *(new NinjaTrap("Takeido"));
	std::cout << "Creating some other claptraps for the ninja to attack" << std::endl;
	ClapTrap	&claptrap = *(new ClapTrap());
	FragTrap	&fragtrap = *(new FragTrap("Didier"));
	ScavTrap	&scavtrap = *(new ScavTrap("Robert"));
	NinjaTrap	&ninjatrap = *(new NinjaTrap("Kodesai"));

	std::cout << std::endl << "Now Takeido attacks the 4 other claptraps :" << std::endl;
	ninja.ninjaShoebox(fragtrap);
	ninja.ninjaShoebox(scavtrap);
	ninja.ninjaShoebox(ninjatrap);
	ninja.ninjaShoebox(claptrap);
	std::cout << std::endl << "displaying ninja info :" << std::endl;
	ninja.displayInfos();
}

int		main(void)
{
	std::cout << "TESTING FRAGTRAP :" << std::endl << std::endl;
	test_fragtrap();
	std::cout << std::endl << "TESTING SCAVTRAP :" << std::endl << std::endl;
	test_scavtrap();
	std::cout << std::endl << "TESTING NINJATRAP :" << std::endl << std::endl;
	test_ninjatrap();
	return (0);
}