

#ifndef PONY_H
# define PONY_H

#include <string>
#include <iostream>

class Pony
{
	public:
		Pony(int tail_length, int height, std::string &name);
		~Pony();

		void	neigh(void) const;
		void	displayDescr(void) const;

	private:
		int const			_tail_length;
		int const			_height;
		std::string	const	_name;
};

#endif