

#ifndef HOSTNAMEMODULE_H
# define HOSTNAMEMODULE_H

#include <string>
#include "IMonitorModule.hpp"

class HostnameModule : public IMonitorModule
{
	public:
		HostnameModule();

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif