

#ifndef OSINFOSMODULE_H
# define OSINFOSMODULE_H

#include <string>
#include "IMonitorModule.hpp"

class OsInfosModule : public IMonitorModule
{
	public:
		OsInfosModule();

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif