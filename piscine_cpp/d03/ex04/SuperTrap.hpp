

#ifndef SUPERTRAP_H
# define SUPERTRAP_H

#include "ClapTrap.hpp"
#include "NinjaTrap.hpp"
#include "FragTrap.hpp"
#include <string>

class SuperTrap : public NinjaTrap, public FragTrap
{
	public:
		SuperTrap();
		SuperTrap(std::string const &name);
		SuperTrap(SuperTrap &other);
		~SuperTrap();
		SuperTrap	&operator=(SuperTrap &other);

		void				rangedAttack(std::string const & target);
		void				meleeAttack(std::string const & target);
		void				takeDamage(unsigned int amount);
		void				beRepaired(unsigned int amount);
		void				displayInfos();
		unsigned int		getHitPoints();
		unsigned int		getMaxHitPoints();
		unsigned int		getEnergyPoints();
		unsigned int		getMaxEnergyPoints();
		unsigned int		getLevel();
		std::string const	&getName();
		unsigned int		getMeleeAttackDamage();
		unsigned int		getRangedAttackDamage();
		unsigned int		getArmorDamageReduction();
		std::string			&getClassName();
};

#endif