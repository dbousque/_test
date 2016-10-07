

#ifndef PEON_H
# define PEON_H

#include "Victim.hpp"

class Peon : public Victim
{
	public:
		Peon(std::string name);
		Peon(Peon &other);
		virtual ~Peon();

		Peon		&operator=(Peon &other);
		void		getPolymorphed() const;

	private:
		Peon();
};

#endif