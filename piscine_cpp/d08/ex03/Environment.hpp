

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

#include <cstdlib>

class Environment
{
	public:
		Environment();
		Environment(size_t n);
		Environment(Environment const &other);
		virtual ~Environment();

		Environment		&operator=(Environment &other);
		unsigned char	**getDataPointer() const;
		unsigned char	*getDataStart() const;
		size_t			getN() const;

	private:
		unsigned char	*_data_start;
		unsigned char	**_data_pointer;
		size_t			_n;
};

#endif