

#ifndef ENEMY_H
# define ENEMY_H

#include <string>

class Enemy
{
	public:
		Enemy(int hp, std::string const & type);
		Enemy(Enemy &other);
		virtual ~Enemy();

		Enemy				&operator=(Enemy &other);
		std::string const	&getType() const;
		int					getHP() const;
		virtual void		takeDamage(int amount);

	private:
		Enemy();

	protected:
		std::string const	&_type;
		int					_hp;
};

#endif