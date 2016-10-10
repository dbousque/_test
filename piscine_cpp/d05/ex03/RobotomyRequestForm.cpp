

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string const target) :
	Form("RobotomyRequestForm", 72, 45)
{
	this->setTarget(target);
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &other) :
	Form(other)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm	&RobotomyRequestForm::operator=(RobotomyRequestForm &other)
{
	return *(new RobotomyRequestForm(other));
}

void		RobotomyRequestForm::action(Bureaucrat const &) const
{
	static bool	already_called = false;

	if (!already_called)
	{
		already_called = true;
		srand(time(NULL));
	}
	std::cout << "Bzz Bzz Bzz !" << std::endl;
	if (rand() % 2 == 0)
		std::cout << this->getTarget() << " has been successfully robotomized" << std::endl;
	else
		throw CouldNotBeRobotomized(this->getTarget());
}

RobotomyRequestForm::CouldNotBeRobotomized::CouldNotBeRobotomized(std::string target) throw() :
	std::exception(),
	_target(target)
{
}

RobotomyRequestForm::CouldNotBeRobotomized::~CouldNotBeRobotomized() throw()
{
}

const char* RobotomyRequestForm::CouldNotBeRobotomized::what() const throw()
{
	return (this->_target + " could not be robotomized").c_str();
}