

#ifndef VICTIM_H
# define VICTIM_H

#include <string>
#include <iostream>

class Victim
{
	public:
		Victim(std::string name);
		Victim(Victim &other);
		virtual ~Victim();

		Victim			&operator=(Victim &other);
		std::string		&getName();
		virtual void	getPolymorphed() const;

	protected:
		Victim();
		std::string	_name;
};

std::ostream	&operator<<(std::ostream &os, Victim &vict);

#endif