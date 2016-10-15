

#include "CpuModule.hpp"

CpuModule::CpuModule()
{
	std::string	*str = new std::string("CPU");
	int 	*usage = new int;
	*usage = 17;
	int 	*usage2 = new int;
	*usage2 = 0;
	int 	*usage3 = new int;
	*usage3 = 29;
	int 	*usage4 = new int;
	*usage4 = 4;
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(usage), Field::INTEGER_PERCENT));
	this->_fields.push_back(new Field(static_cast<void*>(usage2), Field::INTEGER_PERCENT));
	this->_fields.push_back(new Field(static_cast<void*>(usage3), Field::INTEGER_PERCENT));
	this->_fields.push_back(new Field(static_cast<void*>(usage4), Field::INTEGER_PERCENT));
}

void				CpuModule::update()
{

}

std::vector<Field*>	*CpuModule::getFields()
{
	return &(this->_fields);
}