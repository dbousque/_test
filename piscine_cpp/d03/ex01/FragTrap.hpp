

#ifndef FRAGTRAP_H
# define FRAGTRAP_H

#include <string>

class FragTrap
{
	public:
		FragTrap();
		FragTrap(std::string const &name);
		FragTrap(FragTrap &other);
		~FragTrap();
		FragTrap	&operator=(FragTrap &other);

		void				rangedAttack(std::string const & target);
		void				meleeAttack(std::string const & target);
		void				snore(std::string const & target);
		void				myAttack2(std::string const & target);
		void				myAttack3(std::string const & target);
		void				takeDamage(unsigned int amount);
		void				beRepaired(unsigned int amount);
		void				vaulthunter_dot_exe(std::string const & target);
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