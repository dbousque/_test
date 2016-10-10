

#ifndef OFFICEBLOCK_H
# define OFFICEBLOCK_H

#include "Intern.hpp"
#include "Bureaucrat.hpp"

class OfficeBlock
{
	public:
		OfficeBlock();
		OfficeBlock(Intern *intern, Bureaucrat *signing, Bureaucrat *executing);
		virtual ~OfficeBlock();

		void	doBureaucracy(std::string form_name, std::string target);
		void	setIntern(Intern *intern);
		void	setSigningBureaucrat(Bureaucrat *signing);
		void	setExecutingBureaucrat(Bureaucrat *executing);

		class IncompleteOfficeBlockException : std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class NoSuchFormException : std::exception
		{
			public:
				virtual const char* what() const throw();
		};

	private:
		OfficeBlock(OfficeBlock &other);

		OfficeBlock	&operator=(OfficeBlock &other);

		Intern		*_intern;
		Bureaucrat	*_signing_bureaucrat;
		Bureaucrat	*_executing_bureaucrat;
};

#endif