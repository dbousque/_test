

#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

#include <string>
#include <iostream>
#include "Form.hpp"

class Bureaucrat
{
	public:
		Bureaucrat(std::string const name, int grade);
		Bureaucrat(Bureaucrat &other);
		virtual ~Bureaucrat();

		Bureaucrat			&operator=(Bureaucrat &other);
		void				incrementGrade();
		void				decrementGrade();
		void				signForm(Form &form);
		std::string const	getName() const;
		int					getGrade() const;

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

	private:
		Bureaucrat();
		std::string const	_name;
		int					_grade;
};

std::ostream	&operator<<(std::ostream &os, Bureaucrat &bureaucrat);

#endif