

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include "OfficeBlock.hpp"
#include "CentralBureaucracy.hpp"

void	test_do_bureaucracy(OfficeBlock *ob, std::string form_name)
{
	std::cout << "Calling doBureaucracy with form_name " << form_name << " : " << std::endl;
	try
	{
		ob->doBureaucracy(form_name, "Dédé");
		std::cout << "SUCCESS!" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception while calling doBureaucracy : " << e.what() << std::endl;
	}
}

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

	std::cout << std::endl << "TESTING OFFICEBLOCK" << std::endl << std::endl;
	OfficeBlock	ob;
	std::cout << "Testing doBureaucracy with 3 missing fields" << std::endl;
	test_do_bureaucracy(&ob, "salut");
	ob.setSigningBureaucrat(&bernard);
	ob.setExecutingBureaucrat(&bernard);
	std::cout << std::endl << "Testing doBureaucracy with 1 missing field" << std::endl;
	test_do_bureaucracy(&ob, "salut");
	Intern	rand_intern;
	ob.setIntern(&rand_intern);
	std::cout << std::endl << "Testing doBureaucracy with bad form" << std::endl;
	test_do_bureaucracy(&ob, "salut");
	std::cout << std::endl << "Testing doBureaucracy with too low grades" << std::endl;
	test_do_bureaucracy(&ob, "presidential pardon");
	ob.setSigningBureaucrat(&jose);
	ob.setExecutingBureaucrat(&jose);
	std::cout << std::endl << "Testing doBureaucracy with ok grades" << std::endl;
	test_do_bureaucracy(&ob, "presidential pardon");

	std::cout << std::endl << "TESTING CENTRALBUREAUCRACY : " << std::endl;
	std::cout << "Creating CentralBureaucracy and adding 50 bureaucrats (10 too much)" << std::endl;
	CentralBureaucracy	central;
	for (int i = 0; i < 20; i++)
		central.feedBureaucrat(&bernard);
	for (int i = 0; i < 30; i++)
		central.feedBureaucrat(&jose);
	std::cout << "Adding 100 targets to handle" << std::endl;
	for (int i = 0; i < 100; i++)
		central.queueUp("target n" + std::to_string(i));
	std::cout << "Ready for some weird magic ?" << std::endl << std::endl;
	central.doBureaucracy();
	return (0);
}