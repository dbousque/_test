

#ifndef CLAPTRAP_H
# define CLAPTRAP_H

#include <string>

class ClapTrap
{
	public:
		ClapTrap();
		ClapTrap(std::string const &name,
			unsigned int hit_points,
			unsigned int max_hit_points,
			unsigned int energy_points,
			unsigned int max_energy_points,
			unsigned int level,
			unsigned int melee_attack_damage,
			unsigned int ranged_attack_damage,
			unsigned int carmor_damage_reduction,
			std::string &class_name);
		ClapTrap(ClapTrap &other);
		~ClapTrap();
		ClapTrap	&operator=(ClapTrap &other);

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

	protected:
		unsigned int		_hit_points;
		unsigned int		_max_hit_points;
		unsigned int		_energy_points;
		unsigned int		_max_energy_points;
		unsigned int		_level;
		std::string const	&_name;
		unsigned int		_melee_attack_damage;
		unsigned int		_ranged_attack_damage;
		unsigned int		_armor_damage_reduction;
		std::string			_class_name;

	private:
};

#endif