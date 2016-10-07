

#ifndef SORCERER_H
# define SORCERER_H

#include <string>
#include <iostream>
#include "Victim.hpp"

class Sorcerer
{
	public:
		Sorcerer(std::string name, std::string title);
		Sorcerer(Sorcerer &other);
		~Sorcerer();

		Sorcerer	&operator=(Sorcerer &other);
		std::string	&getName();
		std::string	&getTitle();
		void		polymorph(Victim const &) const;

	private:
		Sorcerer();
		std::string			_name;
		std::string			_title;
};

std::ostream	&operator<<(std::ostream &os, Sorcerer &sorc);

#endif