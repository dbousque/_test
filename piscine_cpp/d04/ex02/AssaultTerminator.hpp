

#ifndef ASSAULTTERMINATOR_H
# define ASSAULTTERMINATOR_H

#include "ISpaceMarine.hpp"

class AssaultTerminator : public ISpaceMarine
{
	public:
		AssaultTerminator();
		AssaultTerminator(AssaultTerminator &other);
		virtual ~AssaultTerminator();
		
		AssaultTerminator	&operator=(AssaultTerminator &other);
		AssaultTerminator*	clone() const;
		void				battleCry() const;
		void				rangedAttack() const;
		void				meleeAttack() const;
};

#endif