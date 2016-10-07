

#ifndef CAVAL_H
# define CAVAL_H

#include "Victim.hpp"

class Caval : public Victim
{
	public:
		Caval(std::string name);
		Caval(Caval &other);
		virtual ~Caval();

		Caval		&operator=(Caval &other);
		void		getPolymorphed() const;

	private:
		Caval();
};

#endif