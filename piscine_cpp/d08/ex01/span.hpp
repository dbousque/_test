

#ifndef SPAN_H
# define SPAN_H

#include <vector>
#include <algorithm>

class Span
{
	public:
		Span();
		Span(unsigned int n);
		Span(Span const &other);
		virtual ~Span();

		Span	&operator=(Span &other);
		void	addNumber(int x);

		template <typename Iterator>
		void	addIterRange(Iterator iter_begin, Iterator iter_end)
		{
			for (Iterator iter = iter_begin; iter != iter_end; iter++)
				this->addNumber(*iter);
		}

		int		shortestSpan();
		int		longestSpan();
		std::vector<int> const	&getVals() const;
		unsigned int			getN() const;

	private:

		std::vector<int>	_vals;
		unsigned int		_n;
};

#endif