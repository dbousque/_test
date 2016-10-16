#ifndef HOSTNAMEMODULE_H
# define HOSTNAMEMODULE_H

#include <string>
#include "IMonitorModule.hpp"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <sys/file.h>
#include <pwd.h>


class HostnameModule : public IMonitorModule
{
	public:
		HostnameModule();
		HostnameModule(HostnameModule &other);
		virtual ~HostnameModule();

		HostnameModule	&operator=(HostnameModule &other);
		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif
