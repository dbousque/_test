

#ifndef CENTRALBUREAUCRACY_H
# define CENTRALBUREAUCRACY_H

#include "OfficeBlock.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

class CentralBureaucracy
{
	public:
		CentralBureaucracy();
		CentralBureaucracy(CentralBureaucracy &other);
		virtual ~CentralBureaucracy();

		CentralBureaucracy	&operator=(CentralBureaucracy &other);
		void				feedBureaucrat(Bureaucrat *bureaucrat);
		void				queueUp(std::string target);
		void				doBureaucracy();
		OfficeBlock			*getOfficeBlocks();
		int					getNbBureaucrats();
		std::string			*getQueuedForms();
		int					getQueueSize();
		int					getQueueLen();

	private:
		Intern		_overbooked_intern;
		OfficeBlock	*_office_blocks;
		int			_nb_bureaucrats;
		std::string	*_queued_forms;
		int			_queue_size;
		int			_queue_len;
};

#endif