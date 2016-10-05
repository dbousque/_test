

#ifndef FIXED_H
# define FIXED_H

#include <iostream>

class Fixed
{
	public:
		Fixed();
		~Fixed();
		Fixed(Fixed const &other);
		Fixed(int const n);
		Fixed(float const n);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

		Fixed	&operator=(Fixed const &other);

	private:
		static int const	_fractional_bits;
		int					_val;
};

std::ostream	&operator<<(std::ostream &os, Fixed const &fix);

#endif