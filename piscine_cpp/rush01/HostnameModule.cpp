#include "HostnameModule.hpp"

HostnameModule::HostnameModule()
{
	/********       FETCH HOSTNAME          *********/

	char hostname[100];
	size_t len;
	int name[] = {CTL_KERN, KERN_OSTYPE};

	len = sizeof(hostname);
	name[0] = CTL_KERN;
	name[1] = KERN_HOSTNAME;

	sysctl(name, 2, &hostname, &len, NULL, 0);

	/********       FETCH USERNAME          *********/

	char username[64] = {0};

    getlogin_r(username, sizeof(username)-1);

	std::string	*str = new std::string("HOSTNAME/USERNAME");
	std::string *hostname_str = new std::string(hostname);
	std::string *username_str = new std::string(username);
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(hostname_str), Field::STRING));
	this->_fields.push_back(new Field(static_cast<void*>(username_str), Field::STRING));
}

HostnameModule::HostnameModule(HostnameModule &other) :
	_fields(*(other.getFields()))
{
}

HostnameModule::~HostnameModule()
{
}

HostnameModule	&HostnameModule::operator=(HostnameModule &other)
{
	this->_fields = *(other.getFields());
	return *this;
}

void				HostnameModule::update()
{

}

std::vector<Field*>	*HostnameModule::getFields()
{
	return &(this->_fields);
}
