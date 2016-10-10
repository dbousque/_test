

#include "ShrubberyCreationForm.hpp"
#include <fstream>

std::string	trees[] = {
	std::string("               ,@@@@@@@,                 "),
	std::string("       ,,,.   ,@@@@@@/@@,  .oo8888o.     "),
	std::string("    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o    "),
	std::string("   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'   "),
	std::string("   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'   "),
	std::string("   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'    "),
	std::string("   `&%\\ ` /%&'    |.|        \\ '|8'      "),
	std::string("       |o|        | |         | |        "),
	std::string("       |.|        | |         | |        "),
	std::string("    \\/ ._\\//_/__/  ,\\_//__\\/.  \\_//__/_")
};

ShrubberyCreationForm::ShrubberyCreationForm(std::string const target) :
	Form("ShrubberyCreationForm", 145, 137)
{
	this->setTarget(target);
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &other) :
	Form(other)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(ShrubberyCreationForm &other)
{
	return *(new ShrubberyCreationForm(other));
}

void					ShrubberyCreationForm::action(Bureaucrat const &) const
{
	std::ofstream	ofs(this->getTarget() + "_shrubbery");

	for (int i = 0; i < 10; i++)
		ofs << trees[i] << std::endl;
	ofs.close();
}