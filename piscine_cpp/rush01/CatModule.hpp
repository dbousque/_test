#ifndef CATMODULE_H
# define CATMODULE_H

#include <iostream>
#include <string>
#define FRAME 10

#include "IMonitorModule.hpp"


class CatModule : public IMonitorModule
{
	public:
		CatModule();
		CatModule(CatModule &other);
		virtual ~CatModule();

		CatModule	&operator=(CatModule &other);

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
};

#endif