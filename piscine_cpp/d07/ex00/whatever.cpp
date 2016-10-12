

#include <iostream>
#include <string>

class ExampleClass
{
	public:
		ExampleClass()
		{
		}

		ExampleClass(float val) :
			_val( val)
		{
		}

		ExampleClass(ExampleClass &other) :
			_val(other.getVal())
		{
		}

		virtual ~ExampleClass()
		{
		}

		ExampleClass	&operator=(ExampleClass const &other)
		{
			this->_val = other.getVal();
			return *this;
		}

		float	getVal() const
		{
			return this->_val;
		}

		bool	operator==(ExampleClass const &other)
		{ 
			return (this->_val == other.getVal());
		}

		bool	operator<=(ExampleClass const &other)
		{ 
			return (this->_val <= other.getVal());
		}

		bool	operator>=(ExampleClass const &other)
		{ 
			return (this->_val >= other.getVal());
		}

		bool	operator<(ExampleClass const &other)
		{ 
			return (this->_val < other.getVal());
		}

		bool	operator>(ExampleClass const &other)
		{ 
			return (this->_val > other.getVal());
		}

		bool operator!=(ExampleClass const &other)
		{ 
			return (this->_val != other.getVal());
		}

	private:
		float	_val;
};

std::ostream	&operator<<(std::ostream &os, ExampleClass const &aw)
{
	os << "ExampleClass(" << aw.getVal() << ")";
	return os; 
}

template <typename T>
void	swap(T const &arg1, T const &arg2)
{
	T	&non_const = const_cast<T&>(arg1);
	T 	tmp(non_const);

	tmp = non_const;
	*(static_cast<T*>(&(const_cast<T&>(arg1)))) = arg2;
	*(static_cast<T*>(&(const_cast<T&>(arg2)))) = tmp;
}

template <typename T>
T const 	&min(T const &arg1, T const &arg2)
{
	T	*non_const1 = static_cast<T*>(&(const_cast<T&>(arg1)));
	T	*non_const2 = static_cast<T*>(&(const_cast<T&>(arg2)));

	return (*non_const1 < *non_const2 ? arg1 : arg2);
}

template <typename T>
T const 	&max(T const &arg1, T const &arg2)
{
	T	*non_const1 = static_cast<T*>(&(const_cast<T&>(arg1)));
	T	*non_const2 = static_cast<T*>(&(const_cast<T&>(arg2)));

	return (*non_const1 > *non_const2 ? arg1 : arg2);
}

void	my_assert(bool cond)
{
	if (!cond)
		throw std::exception();
}

int		main(void)
{
	int		a = 2;
	int		b = 3;

	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap( c, d );
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;

	std::cout << std::endl << "Doing the same with my ExampleClass : " << std::endl;
	ExampleClass 	aw(10.2);
	ExampleClass	bw(11.5);
	::swap( aw, bw );
	std::cout << "aw = " << aw << ", bw = " << bw << std::endl;
	std::cout << "min( aw, bw ) = " << ::min( aw, bw ) << std::endl;
	std::cout << "max( aw, bw ) = " << ::max( aw, bw ) << std::endl;

	std::cout << std::endl << "Doing the same again, but with const ExampleClass : " << std::endl;
	ExampleClass const 	aw2(10.2);
	ExampleClass const	bw2(11.5);
	::swap( aw2, bw2 );
	std::cout << "aw2 = " << aw2 << ", bw2 = " << bw2 << std::endl;
	std::cout << "min( aw2, bw2 ) = " << ::min( aw2, bw2 ) << std::endl;
	std::cout << "max( aw2, bw2 ) = " << ::max( aw2, bw2 ) << std::endl;

	std::cout << std::endl << "Asserting return values of min and max are second values when arguments are equal :" << std::endl;
	ExampleClass const 	aw3(11.5);
	ExampleClass const	bw3(11.5);
	my_assert(&bw3 == &(min(aw3, bw3)));
	std::cout << "ok" << std::endl;
	my_assert(&bw3 == &(max(aw3, bw3)));
	std::cout << "ok" << std::endl;

	return (0);
}