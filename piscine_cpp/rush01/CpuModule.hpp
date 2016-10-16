#ifndef CPUMODULE_H
# define CPUMODULE_H

#include <string>
#include "IMonitorModule.hpp"
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <utility>


class CpuModule : public IMonitorModule
{
	public:
		CpuModule();
		CpuModule(CpuModule &other);
		virtual ~CpuModule();

		CpuModule	&operator=(CpuModule &other);
		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
		float 				_getCPULoad();
		float				_calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
		int64_t				_previousTotalTicks;
		int64_t				_previousIdleTicks;
		int					_getCPUActivity();
};

#endif