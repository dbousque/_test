

#include <iostream>

template <typename T>
void	iter(T const array[], size_t length, void (*func)(T const &))
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

template <typename T>
void	iter(T *array[], size_t length, void (*func)(T *))
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

void	print_string(char *str)
{
	std::cout << str << std::endl;
}

void	print_string_const(char const *str)
{
	std::cout << str << std::endl;
}

void	change_first_char_to_a(char *str)
{
	str[0] = 'a';
}

int		main(void)
{
	std::string		*tmp;
	char const		*array_const[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	char			*array[10];

	for (int i = 0; i < 10; i++)
	{
		tmp = new std::string((std::to_string(i)));
		array[i] = const_cast<char*>(tmp->c_str());
	}

	std::cout << "Calling print_string on array" << std::endl;
	iter(array, 10, print_string);

	std::cout << "Calling print_string on array_const" << std::endl;
	iter(array_const, 10, print_string_const);

	std::cout << std::endl << "Calling change_first_char_to_a and then print_string on array" << std::endl;
	iter(array, 10, change_first_char_to_a);
	iter(array, 10, print_string);
	return (0);
}