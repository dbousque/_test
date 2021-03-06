

#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

#include <exception>
#include <string>
#include <iostream>

class Bureaucrat
{
	public:
		Bureaucrat(std::string const name, int grade) throw(std::exception);
		Bureaucrat(Bureaucrat &other) throw(std::exception);
		virtual ~Bureaucrat();

		Bureaucrat			&operator=(Bureaucrat &other);
		void				incrementGrade();
		void				decrementGrade();
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