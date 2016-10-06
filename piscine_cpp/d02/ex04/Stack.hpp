

#ifndef STACK_H
# define STACK_H

#include "List.hpp"

class Stack
{
	public:
		Stack();
		Stack(Stack &other);
		~Stack();

		Stack	&operator=(Stack &other);

		void	push(void *elt);
		void	*pop();
		void	*getTop();
		size_t	length();
		List	&toList();

	private:
		List	&_lst;
};

#endif