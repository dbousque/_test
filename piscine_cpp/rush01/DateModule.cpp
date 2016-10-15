

#include "DateModule.hpp"

DateModule::DateModule()
{
	std::string	*str = new std::string("TIME");
	std::string	*str2 = new std::string("2016 10 15");
	std::string	*str3 = new std::string("18:47");
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(str2), Field::STRING));
	this->_fields.push_back(new Field(static_cast<void*>(str3), Field::STRING));
}

void				DateModule::update()
{

}

std::vector<Field*>	*DateModule::getFields()
{
	return &(this->_fields);
}