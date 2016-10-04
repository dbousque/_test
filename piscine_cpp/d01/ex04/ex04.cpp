

#include <string>
#include <iostream>

std::string	*get_str_ptr(std::string *str)
{
	return (str);
}

std::string	&get_str_ref(std::string *str)
{
	return (*str);
}

int		main(void)
{
	std::string	my_str = "HI THIS IS BRAIN";
	std::string	*str_ptr = get_str_ptr(&my_str);
	std::string	&str_ref = get_str_ref(&my_str);

	std::cout << "Printing the string through the pointer   : " << *str_ptr << std::endl;
	std::cout << "Printing the string through the reference : " << str_ref << std::endl;
	return (0);
}