

#include "HostnameModule.hpp"
#include "OsInfosModule.hpp"
#include "DateModule.hpp"
#include "CpuModule.hpp"
#include "monitorShell.hpp"
#include <sys/time.h>
#include <unistd.h>

int				TARGET_FRAMERATE = 5;
unsigned long	TO_WAIT_PER_FRAME = 1000 / TARGET_FRAMERATE;

unsigned long	getCurrentMillis()
{
	struct timeval	t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

int		main()
{
	monitorShell	monitor;
	std::vector<IMonitorModule*>	modules;

	modules.push_back(new HostnameModule());
	modules.push_back(new OsInfosModule());
	modules.push_back(new DateModule());
	modules.push_back(new CpuModule());
	unsigned long	start;
	unsigned long	end;

	for(;;) {
		start = getCurrentMillis();
		erase();
		monitor.displayModules(modules);
		refresh();
		end = getCurrentMillis();
		if (start + TO_WAIT_PER_FRAME > end)
			usleep((TO_WAIT_PER_FRAME - (end - start)) * 1000);
	}
	return (0);
}
