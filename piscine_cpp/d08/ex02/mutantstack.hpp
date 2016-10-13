

#ifndef MUTANTSTACK_H
# define MUTANTSTACK_H

#include <stack>
#include <deque>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
		MutantStack() :
			std::stack<T>()
		{
		}

		MutantStack(MutantStack const &other) :
			std::stack<T>(other)
		{
		}

		virtual ~MutantStack()
		{
		}

		MutantStack					&operator=(MutantStack &other)
		{
			return *(new MutantStack(other));
		}

		typename std::deque<T>::iterator	begin()
		{
			return this->c.begin();
		}

		typename std::deque<T>::iterator	end()
		{
			return this->c.end();
		}

		typedef typename std::stack<T>::container_type::iterator iterator;
};

#endif