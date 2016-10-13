

#include "span.hpp"
#include <iostream>

int main()
{
	Span sp = Span(5);

	srand(time(NULL));
	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	std::cout << std::endl;
	std::cout << "creating a random vector of 10 elements and adding it with Span::addIterRange to a void span" << std::endl;
	std::vector<int>	vect;
	for (int i = 0; i < 10; i++)
		vect.push_back(rand() % 100);
	std::cout << "res vector : [";
	for (std::vector<int>::iterator iter = vect.begin(); iter != vect.end(); iter++)
		std::cout << *iter << " ";
	std::cout << "]" << std::endl;
	Span sp2(10);
	sp2.addIterRange(vect.begin(), vect.end());
	std::cout << "shortest : " << sp2.shortestSpan() << std::endl;
	std::cout << "longest : " << sp2.longestSpan() << std::endl;

	std::cout << std::endl << "Now testing with 1 000 000 random numbers : " << std::endl;
	Span sp3(1000000);
	for (int i = 0; i < 1000000; i++)
		sp3.addNumber(rand() % 10000000);
	std::cout << "shortest : " << sp3.shortestSpan() << std::endl;
	std::cout << "longest : " << sp3.longestSpan() << std::endl;
	return (0);
}