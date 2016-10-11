

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string const target) :
	Form("PresidentialPardonForm", 25, 5)
{
	this->setTarget(target);
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm &other) :
	Form(other)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(PresidentialPardonForm &other)
{
	return *(new PresidentialPardonForm(other));
}

void		PresidentialPardonForm::action(Bureaucrat const &) const
{
	std::cout << this->getTarget() << " has been pardoned by Zafod Beeblebrox" << std::endl;
}