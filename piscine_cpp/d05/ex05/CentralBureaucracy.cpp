

#include "CentralBureaucracy.hpp"

std::string		forms_names[3] = {
	std::string("shrubbery creation"),
	std::string("robotomy request"),
	std::string("presidential pardon")
};

CentralBureaucracy::CentralBureaucracy()
{
	this->_office_blocks = new OfficeBlock[20];
	for (int i = 0; i < 20; i++)
		this->_office_blocks[i].setIntern(&this->_overbooked_intern);
	this->_nb_bureaucrats = 0;
	this->_queued_forms = new std::string[16];
	this->_queue_size = 16;
	this->_queue_len = 0;
}

CentralBureaucracy::CentralBureaucracy(CentralBureaucracy &other)
{
	this->_office_blocks = other.getOfficeBlocks();
	this->_nb_bureaucrats = other.getNbBureaucrats();
	this->_queued_forms = other.getQueuedForms();
	this->_queue_size = other.getQueueSize();
	this->_queue_len = other.getQueueLen();
}

CentralBureaucracy::~CentralBureaucracy()
{
	delete [] this->_office_blocks;
	delete [] this->_queued_forms;
}

CentralBureaucracy	&CentralBureaucracy::operator=(CentralBureaucracy &other)
{
	return *(new CentralBureaucracy(other));
}

void				CentralBureaucracy::feedBureaucrat(Bureaucrat *bureaucrat)
{
	if (this->_nb_bureaucrats >= 40)
		return ;
	if (this->_nb_bureaucrats % 2 == 0)
		this->_office_blocks[this->_nb_bureaucrats / 2].setExecutingBureaucrat(bureaucrat);
	else
		this->_office_blocks[this->_nb_bureaucrats / 2].setSigningBureaucrat(bureaucrat);
	this->_nb_bureaucrats++;
}

void				CentralBureaucracy::queueUp(std::string target)
{
	if (this->_queue_len == this->_queue_size)
	{
		this->_queue_size *= 2;
		std::string	*new_queue = new std::string[this->_queue_size];
		for (int i = 0; i < this->_queue_len; i++)
			new_queue[i] = this->_queued_forms[i];
		delete [] this->_queued_forms;
		this->_queued_forms = new_queue;
	}
	this->_queued_forms[this->_queue_len] = target;
	this->_queue_len++;
}

void	CentralBureaucracy::doBureaucracy()
{
	int				i;
	std::string		*current_form;

	i = 0;
	current_form = &(forms_names[rand() % 3]);
	while (i < this->_queue_len)
	{
		for (int x = 0; x < 20 && i < this->_queue_len; x++)
		{
			try
			{
				this->_office_blocks[x].doBureaucracy(*current_form, this->_queued_forms[i]);
				i++;
				current_form = &(forms_names[rand() % 3]);
			}
			catch (std::exception &)
			{
				std::cout << "This OfficeBlock was not able to handle this form, passing to next OfficeBlock" << std::endl;
			}
		}
	}
	this->_queue_len = 0;
}

OfficeBlock			*CentralBureaucracy::getOfficeBlocks()
{
	return this->_office_blocks;
}

int					CentralBureaucracy::getNbBureaucrats()
{
	return this->_nb_bureaucrats;
}

std::string			*CentralBureaucracy::getQueuedForms()
{
	return this->_queued_forms;
}

int					CentralBureaucracy::getQueueSize()
{
	return this->_queue_size;
}

int					CentralBureaucracy::getQueueLen()
{
	return this->_queue_len;
}