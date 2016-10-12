

#include "Array.hpp"
#include <iostream>

void	my_assert(bool cond)
{
	if (!cond)
		std::cout << "Assertion failed" << std::endl;
}

class MyInteger
{
	public:
		MyInteger() :
			_val(0)
		{
		}

		MyInteger(MyInteger &other) :
			_val(other.getVal())
		{
		}

		~MyInteger()
		{
		}

		MyInteger	&operator=(int n)
		{
			this->_val = n;
			return *this;
		}

		MyInteger	&operator=(MyInteger &other)
		{
			this->_val = other.getVal();
			return *this;
		}

		int		getVal() const
		{
			return this->_val;
		}

	private:
		int		_val;
};

std::ostream	&operator<<(std::ostream &os, MyInteger &myinteger)
{
	os << "Int(" << myinteger.getVal() << ")";
	return os;
}

template <typename T>
void	test()
{
	std::cout << "Calling Array() and asserting that size() == 0" << std::endl;
	Array<T>	arr1;
	my_assert(arr1.size() == 0);
	std::cout << "ok" << std::endl;
	std::cout << "checking that [0] over this array throws an exception" << std::endl;
	try
	{
		arr1[0];
		std::cout << "not ok" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << "ok" << std::endl;
	}
	std::cout << "Creating Array<T>(10)" << std::endl;
	Array<T>	arr2(10);
	std::cout << "setting first 5 elements to 10 and the 5 next to 20, and displaying the array : " << std::endl;
	for (int i = 0; i < 5; i++)
		arr2[i] = 10;
	for (int i = 5; i < 10; i++)
		arr2[i] = 20;
	for (int i = 0; i < 10; i++)
		std::cout << arr2[i] << " ";
	std::cout << std::endl;
	std::cout << "Copying the array through the copy constructor, changing values in the original, and displaying both : " << std::endl;
	Array<T>	arr3(arr2);
	for (int i = 0; i < 5; i++)
		arr2[i] = 40;
	std::cout << "original : ";
	for (int i = 0; i < 10; i++)
		std::cout << arr2[i] << " ";
	std::cout << std::endl << "copy : ";
	for (int i = 0; i < 10; i++)
		std::cout << arr3[i] << " ";
	std::cout << std::endl;
}

int		main(void)
{
	test<int>();
	std::cout << std::endl << "Doing the same with MyInteger : " << std::endl;
	test<MyInteger>();
	return (0);
}