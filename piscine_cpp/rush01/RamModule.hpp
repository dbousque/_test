

#ifndef RAMMODULE_H
# define RAMMODULE_H

#include "IMonitorModule.hpp"
#include <string>

class RamModule : public IMonitorModule
{
	public:
		RamModule();
		RamModule(RamModule &other);
		virtual ~RamModule();

		RamModule	&operator=(RamModule &other);
		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif
