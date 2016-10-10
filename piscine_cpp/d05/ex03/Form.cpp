

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(std::string const name, int grade_required_to_sign, int grade_required_to_execute) :
	_name(name),
	_signed(false),
	_grade_required_to_sign(grade_required_to_sign),
	_grade_required_to_execute(grade_required_to_execute)
{
	if (grade_required_to_sign > 150)
		throw GradeTooLowException();
	if (grade_required_to_sign < 1)
		throw GradeTooHighException();
	if (grade_required_to_execute > 150)
		throw GradeTooLowException();
	if (grade_required_to_execute < 1)
		throw GradeTooHighException();
}

Form::Form(Form &other) :
	_target(other.getTarget()),
	_name(other.getName()),
	_signed(other.getSigned()),
	_grade_required_to_sign(other.getGradeRequiredToSign()),
	_grade_required_to_execute(other.getGradeRequiredToExecute())
{
}

Form::~Form()
{
}

Form				&Form::operator=(Form &other)
{
	(void)other;
	return *this;
}

void				Form::beSigned(Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_grade_required_to_sign)
		throw GradeTooLowException();
	this->_signed = true;
}

void			Form::setTarget(std::string target)
{
	this->_target = target;
}

void			Form::execute(Bureaucrat const &executor) const
{
	if (!this->_signed)
		throw FormNotSignedException();
	if (executor.getGrade() > this->_grade_required_to_execute)
		throw GradeTooLowException();
	this->action(executor);
}

std::string 		Form::getTarget() const
{
	return this->_target;
}

std::string const	Form::getName() const
{
	return this->_name;
}

bool				Form::getSigned() const
{
	return this->_signed;
}

int				Form::getGradeRequiredToSign() const
{
	return this->_grade_required_to_sign;
}

int				Form::getGradeRequiredToExecute() const
{
	return this->_grade_required_to_execute;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Grade too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Grade too low";
}

const char* Form::FormNotSignedException::what() const throw()
{
	return "Form not signed";
}

std::ostream	&operator<<(std::ostream &os, Form &form)
{
	os << form.getName() << (form.getSigned() ? ",    " : ", not") << " signed";
	os << ", grade required to sign : " << form.getGradeRequiredToSign();
	os << ", grade required to execute : " << form.getGradeRequiredToExecute() << std::endl;
	return os;
}