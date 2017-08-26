

#include <iostream>

class Base
{
	public:
		virtual ~Base() {};
};

class A : public Base
{
};

class B : public Base
{
};

class C : public Base
{
};

Base	*generate()
{
	static bool	already_called = false;
	int			random_int;

	if (!already_called)
	{
		already_called = true;
		srand(time(NULL));
	}
	random_int = rand() % 3;
	if (random_int == 0)
		return new A;
	if (random_int == 1)
		return new B;
	return new C;
}

void	identify_from_pointer(Base *p)
{
	A 		*a;
	B		*b;
	C		*c;

	a = dynamic_cast<A*>(p);
	if (a)
	{
		std::cout << "A" << std::endl;
		return ;
	}
	b = dynamic_cast<B*>(p);
	if (b)
	{
		std::cout << "B" << std::endl;
		return ;
	}
	c = dynamic_cast<C*>(p);
	if (c)
		std::cout << "C" << std::endl;
}

void	identify_from_reference(Base &p)
{
	identify_from_pointer(&p);
}

int		main(void)
{
	A 		*a = new A;
	B		*b = new B;
	C		*c = new C;
	Base	*base = new Base;
	Base	*tmp;

	std::cout << "Calling identify_from_pointer with an A :" << std::endl;
	identify_from_pointer(static_cast<Base*>(a));
	std::cout << "Calling identify_from_pointer with a B :" << std::endl;
	identify_from_pointer(static_cast<Base*>(b));
	std::cout << "Calling identify_from_pointer with a C :" << std::endl;
	identify_from_pointer(static_cast<Base*>(c));
	std::cout << "Calling identify_from_pointer with a Base :" << std::endl;
	identify_from_pointer(base);

	std::cout << std::endl << std::endl;
	std::cout << "Calling identify_from_reference with an A :" << std::endl;
	identify_from_reference(static_cast<Base&>(*a));
	std::cout << "Calling identify_from_reference with a B :" << std::endl;
	identify_from_reference(static_cast<Base&>(*b));
	std::cout << "Calling identify_from_reference with a C :" << std::endl;
	identify_from_reference(static_cast<Base&>(*c));
	std::cout << "Calling identify_from_reference with a Base :" << std::endl;
	identify_from_reference(*base);

	std::cout << std::endl << std::endl;
	std::cout << "Calling identify_from_pointer 10 times with randomnly generated Base childs :" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		tmp = generate();
		identify_from_pointer(tmp);
		delete tmp;
	}

	delete a;
	delete b;
	delete c;
	delete base;
	return (0);
}