

#include "Bureaucrat.hpp"

int		main(void)
{
	std::cout << "creating a bureaucrat with grade 10 : " << std::endl;
	Bureaucrat jose("Jose", 10);
	std::cout << jose;
	std::cout << "Incrementing Jose's grade until exception : " << std::endl;
	while (true)
	{
		try
		{
			jose.incrementGrade();
			std::cout << jose;
		}
		catch (Bureaucrat::GradeTooHighException &e)
		{
			std::cout << e.what() << std::endl;
			break ;
		}
	}
	std::cout << "creating a bureaucrat with grade 140 : " << std::endl;
	Bureaucrat bernard("Bernard", 140);
	std::cout << bernard;
	std::cout << "Decrementing Bernard's grade until exception : " << std::endl;
	while (true)
	{
		try
		{
			bernard.decrementGrade();
			std::cout << bernard;
		}
		catch (Bureaucrat::GradeTooLowException &e)
		{
			std::cout << e.what() << std::endl;
			break ;
		}
	}
	std::cout << "Catching exception at creation of bureaucrat grade 0 : " << std::endl;
	try
	{
		Bureaucrat	herve("Hervé", 0);
		std::cout << "Worked : " << herve;
	}
	catch (Bureaucrat::GradeTooHighException &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Catching exception at creation of bureaucrat grade 151 : " << std::endl;
	try
	{
		Bureaucrat	herve("Hervé", 151);
		std::cout << "Worked : " << herve;
	}
	catch (Bureaucrat::GradeTooLowException &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}