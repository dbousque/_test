

#include "OsInfosModule.hpp"

OsInfosModule::OsInfosModule()
{
	std::string	*str = new std::string("OS");
	std::string	*str2 = new std::string("MAC OSX 10.12");
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(str2), Field::STRING));
}

void				OsInfosModule::update()
{

}

std::vector<Field*>	*OsInfosModule::getFields()
{
	return &(this->_fields);
}