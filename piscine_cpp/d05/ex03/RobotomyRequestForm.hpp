

#ifndef ROBOTOMYREQUESTFORM_H
# define ROBOTOMYREQUESTFORM_H

#include "Form.hpp"

class RobotomyRequestForm : public Form
{
	public:
		RobotomyRequestForm(std::string const target);
		RobotomyRequestForm(RobotomyRequestForm &other);
		virtual ~RobotomyRequestForm();

		RobotomyRequestForm	&operator=(RobotomyRequestForm &other);
		void					action(Bureaucrat const &executor) const;

		class CouldNotBeRobotomized : public std::exception
		{
			public:
				CouldNotBeRobotomized(std::string target) throw();
				virtual ~CouldNotBeRobotomized() throw();
				virtual const char* what() const throw();

			private:
				std::string		_target;
		};

	private:
		RobotomyRequestForm();
};

#endif