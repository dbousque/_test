

#ifndef TACTICALMARINE_H
# define TACTICALMARINE_H

#include "ISpaceMarine.hpp"

class TacticalMarine : public ISpaceMarine
{
	public:
		TacticalMarine();
		TacticalMarine(TacticalMarine &other);
		virtual ~TacticalMarine();
		
		TacticalMarine	&operator=(TacticalMarine &other);
		TacticalMarine*	clone() const;
		void			battleCry() const;
		void			rangedAttack() const;
		void			meleeAttack() const;
};

#endif