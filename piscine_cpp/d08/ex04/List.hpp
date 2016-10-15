

#ifndef LIST_H
# define LIST_H

#include <string>

class List
{
	public:
		List();
		List(List &other);
		~List();

		List	&operator=(List &other);

		void	add(void *elt);
		size_t	length();
		void	*get(size_t n);
		void	*pop();
		void	*getTop();

	private:
		void	**_elts;
		size_t	_len;
		size_t	_size;
		void	_doubleListSize();
};

#endif