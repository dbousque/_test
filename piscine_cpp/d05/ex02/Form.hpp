

#ifndef FORM_H
# define FORM_H

#include <string>
#include <iostream>

class Bureaucrat;

class Form
{
	public:
		Form(std::string const name, int grade_required_to_sign, int grade_required_to_execute);
		Form(Form &other);
		virtual ~Form();

		Form				&operator=(Form &other);
		void				beSigned(Bureaucrat &bureaucrat);
		void				setTarget(std::string target);
		virtual void		action(Bureaucrat const &executor) const = 0;
		void				execute(Bureaucrat const &executor) const;
		std::string			getTarget() const;
		std::string const	getName() const;
		bool				getSigned() const;
		int					getGradeRequiredToSign() const;
		int					getGradeRequiredToExecute() const;

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class FormNotSignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

	private:
		Form();
		std::string			_target;
		std::string const	_name;
		bool				_signed;
		int const			_grade_required_to_sign;
		int const			_grade_required_to_execute;

};

std::ostream	&operator<<(std::ostream &os, Form &form);

#endif