

#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(Intern &)
{
}

Intern::~Intern()
{
}

Intern	&Intern::operator=(Intern &)
{
	return *this;
}

Form	*Intern::_makeShrubberyForm(std::string target)
{
	return new ShrubberyCreationForm(target);
}

Form	*Intern::_makeRobotomyForm(std::string target)
{
	return new RobotomyRequestForm(target);
}

Form	*Intern::_makePresidentialForm(std::string target)
{
	return new PresidentialPardonForm(target);
}

Form	*Intern::makeForm(std::string const form_name, std::string const target)
{
	std::string		funcs_names[3] = {
		std::string("shrubbery creation"),
		std::string("robotomy request"),
		std::string("presidential pardon")
	};

	Form*	(Intern::*forms_funcs[3])(std::string target) = {
		&Intern::_makeShrubberyForm,
		&Intern::_makeRobotomyForm,
		&Intern::_makePresidentialForm
	};

	int		i;
	Form	*res;

	i = 0;
	while (i < 3 && funcs_names[i] != form_name)
		i++;
	if (i == 3)
	{
		std::cout << form_name <<  " : form not found" << std::endl;
		return NULL;
	}
	res = (this->*forms_funcs[i])(target);
	std::cout << "Intern creates " << *res;
	return res;
}