#include "DateModule.hpp"

DateModule::DateModule()
{
	time_t rawtime;
    struct tm * timeinfo;
    char buff1[80];
    char buff2[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buff1,80,"%d-%m-%Y",timeinfo);
    strftime(buff2,80,"%H:%M:%S",timeinfo);

	std::string	*str = new std::string("DATE/TIME");
	std::string	*str2 = new std::string(buff1);
	std::string	*str3 = new std::string(buff2);
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(str2), Field::STRING));
	this->_fields.push_back(new Field(static_cast<void*>(str3), Field::STRING));
}

DateModule::DateModule(DateModule &other) :
    _fields(*(other.getFields()))
{
}

DateModule::~DateModule()
{
}

DateModule   &DateModule::operator=(DateModule &other)
{
    this->_fields = *(other.getFields());
    return *this;
}

void				DateModule::update()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buff1[80];
    char buff2[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buff1,80,"%d-%m-%Y",timeinfo);
	std::string *str1 = new std::string(buff1);

	Field *tmp1 = new Field(static_cast<void*>(str1), Field::STRING);
	delete this->_fields[1];
	this->_fields[1] = tmp1;

    strftime(buff2,80,"%H:%M:%S",timeinfo);
	std::string *str2 = new std::string(buff2);

	Field *tmp2 = new Field(static_cast<void*>(str2), Field::STRING);
	delete this->_fields[2];
    this->_fields[2] = tmp2;
}

std::vector<Field*>	*DateModule::getFields()
{
	return &(this->_fields);
}
