

#ifndef CPUMODULE_H
# define CPUMODULE_H

#include <string>
#include "IMonitorModule.hpp"

class CpuModule : public IMonitorModule
{
	public:
		CpuModule();

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif