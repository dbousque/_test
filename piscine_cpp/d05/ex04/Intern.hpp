

#ifndef INTERN_H
# define INTERN_H

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <string>

class Intern
{
	public:
		Intern();
		Intern(Intern &other);
		virtual ~Intern();

		Intern	&operator=(Intern &other);
		Form	*makeForm(std::string const form_name, std::string const target);

	private:
		Form	*_makeShrubberyForm(std::string target);
		Form	*_makeRobotomyForm(std::string target);
		Form	*_makePresidentialForm(std::string target);
};

#endif