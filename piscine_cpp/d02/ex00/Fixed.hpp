

#ifndef FIXED_H
# define FIXED_H

class Fixed
{
	public:
		Fixed();
		~Fixed();
		Fixed(Fixed const &other);

		Fixed	&operator=(Fixed const &other);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);

	private:
		static int const	_fractional_bits;
		int					_val;
};

#endif