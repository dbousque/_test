

#ifndef DATEMODULE_H
# define DATEMODULE_H

#include <string>
#include "IMonitorModule.hpp"

class DateModule : public IMonitorModule
{
	public:
		DateModule();

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif