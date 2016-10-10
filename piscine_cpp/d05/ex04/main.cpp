

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

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

	std::cout << std::endl << "Creating ShrubberyCreationForm : " << std::endl;
	ShrubberyCreationForm	schrub("target_file");
	RobotomyRequestForm		robot("pony");
	PresidentialPardonForm	pardon("Olivier");
	std::cout << schrub;
	std::cout << std::endl << "Executing form by Bernard : " << std::endl;
	bernard.executeForm(schrub);
	std::cout << std::endl << "Signing form by Jose : " << std::endl;
	jose.signForm(schrub);
	std::cout << schrub;
	std::cout << std::endl << "Executing form by Bernard : " << std::endl;
	bernard.executeForm(schrub);
	std::cout << std::endl << "Executing form by Jose : " << std::endl;
	jose.executeForm(schrub);

	std::cout << std::endl << "executing RobotomyRequestForm 4 times : " << std::endl;
	jose.signForm(robot);
	jose.executeForm(robot);
	jose.executeForm(robot);
	jose.executeForm(robot);
	jose.executeForm(robot);

	std::cout << std::endl << "Making some excuses and being pardoned" << std::endl;
	jose.signForm(pardon);
	jose.executeForm(pardon);

	std::cout << std::endl << "Creating an intern and handing him some forms to make : " << std::endl;
	Intern	my_intern;
	Form	*res;
	std::cout << std::endl;
	res = my_intern.makeForm("robotomy request", "Superlolz");
	if (res)
		std::cout << "res : " << *res;
	else
		std::cout << "res : NULL" << std::endl;
	std::cout << std::endl;
	res = my_intern.makeForm("superlolz", "Superlolz");
	if (res)
		std::cout << "res : " << *res;
	else
		std::cout << "res : NULL" << std::endl;
	std::cout << std::endl;
	res = my_intern.makeForm("presidential pardon", "Superlolz");
	if (res)
		std::cout << "res : " << *res;
	else
		std::cout << "res : NULL" << std::endl;
	std::cout << std::endl;
	res = my_intern.makeForm("a great form please", "Superlolz");
	if (res)
		std::cout << "res : " << *res;
	else
		std::cout << "res : NULL" << std::endl;
	return (0);
}