

#include "OfficeBlock.hpp"

OfficeBlock::OfficeBlock()
{
	this->_intern = NULL;
	this->_signing_bureaucrat = NULL;
	this->_executing_bureaucrat = NULL;
}

OfficeBlock::OfficeBlock(Intern *intern, Bureaucrat *signing, Bureaucrat *executing)
{
	this->_intern = intern;
	this->_signing_bureaucrat = signing;
	this->_executing_bureaucrat = executing;
}

OfficeBlock::~OfficeBlock()
{
}

void	OfficeBlock::doBureaucracy(std::string form_name, std::string target)
{
	Form	*form;

	if (!this->_intern || !this->_signing_bureaucrat || !this->_executing_bureaucrat)
		throw IncompleteOfficeBlockException();
	form = this->_intern->makeForm(form_name, target);
	if (!form)
		throw NoSuchFormException();
}

void	OfficeBlock::setIntern(Intern *intern)
{
	this->_intern = intern;
}

void	OfficeBlock::setSigningBureaucrat(Bureaucrat *signing)
{
	this->_signing_bureaucrat = signing;
}

void	OfficeBlock::setExecutingBureaucrat(Bureaucrat *executing)
{
	this->_executing_bureaucrat = executing;
}

const char* Bureaucrat::IncompleteOfficeBlockException::what() const throw()
{
	return "Incomplete OfficeBlock, please specify all three fields";
}

const char* Bureaucrat::NoSuchFormException::what() const throw()
{
	return "No such form";
}