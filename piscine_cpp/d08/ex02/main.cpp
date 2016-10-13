

#include "mutantstack.hpp"
#include <iostream>

int main()
{
	srand(time(NULL));
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << mstack.top() << std::endl;

	mstack.pop();

	std::cout << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);

	std::cout << std::endl << "Some more tests, creating an empty mutantstack" << std::endl;
	MutantStack<float>	s2;
	std::cout << "stack.empty() : " << (s2.empty() ? "true " : "false") << std::endl;
	std::cout << "adding one float" << std::endl;
	s2.push(13.42);
	std::cout << "stack.empty() : " << (s2.empty() ? "true " : "false") << std::endl;
	std::cout << "adding some random floats and iterating over them : " << std::endl;
	for (int i = 0; i < 10; i++)
		s2.push((static_cast<float>(rand() % 10000)) / 13.18);
	for (MutantStack<float>::iterator iter = s2.begin(); iter != s2.end(); iter++)
		std::cout << *iter << std::endl;
	return 0;
}