

#include "HostnameModule.hpp"

HostnameModule::HostnameModule()
{
	std::string	*str = new std::string("HOSTNAME/USERNAME");
	std::string	*str2 = new std::string("dbousque");
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(str2), Field::STRING));
}

void				HostnameModule::update()
{

}

std::vector<Field*>	*HostnameModule::getFields()
{
	return &(this->_fields);
}