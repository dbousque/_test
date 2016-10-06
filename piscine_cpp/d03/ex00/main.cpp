

#include "FragTrap.hpp"
#include <iostream>

int		main(void)
{
	std::cout << "Creating FragTrap with name Léo" << std::endl;
	FragTrap	&leo = *(new FragTrap("leo"));
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
	return (0);
}