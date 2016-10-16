#ifndef OSINFOSMODULE_H
# define OSINFOSMODULE_H

#include <string>
#include "IMonitorModule.hpp"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <sys/file.h>


class OsInfosModule : public IMonitorModule
{
	public:
		OsInfosModule();
		OsInfosModule(OsInfosModule &other);
		virtual ~OsInfosModule();

		OsInfosModule	&operator=(OsInfosModule &other);

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif