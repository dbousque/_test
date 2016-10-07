

#ifndef SCAVTRAP_H
# define SCAVTRAP_H

#include <string>

class ScavTrap
{
	public:
		ScavTrap();
		ScavTrap(std::string const &name);
		ScavTrap(ScavTrap &other);
		~ScavTrap();
		ScavTrap	&operator=(ScavTrap &other);

		void				rangedAttack(std::string const & target);
		void				meleeAttack(std::string const & target);
		void				challenge1();
		void				challenge2();
		void				challenge3();
		void				takeDamage(unsigned int amount);
		void				beRepaired(unsigned int amount);
		void				challengeNewcomer();
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

	private:
		unsigned int		_hit_points;
		unsigned int		_max_hit_points;
		unsigned int		_energy_points;
		unsigned int		_max_energy_points;
		unsigned int		_level;
		std::string const	&_name;
		unsigned int		_melee_attack_damage;
		unsigned int		_ranged_attack_damage;
		unsigned int		_armor_damage_reduction;
};

#endif