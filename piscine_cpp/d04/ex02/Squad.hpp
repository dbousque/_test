

#ifndef SQUAD_H
# define SQUAD_H

#include "ISquad.hpp"
#include "ISpaceMarine.hpp"

class Squad : public ISquad
{
	public:
		Squad();
		Squad(Squad &other);
		virtual ~Squad();

		Squad			&operator=(Squad &other);
		int				getCount() const;
		ISpaceMarine*	getUnit(int n) const;
		int				push(ISpaceMarine* space_marine);

	private:
		int				_len;
		int				_size;
		ISpaceMarine	**_marines;
};

#endif