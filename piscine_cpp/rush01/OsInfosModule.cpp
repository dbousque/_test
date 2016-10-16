#include "OsInfosModule.hpp"

OsInfosModule::OsInfosModule()
{
/********       FETCH OSNAME          *********/

    char osname[100];
    size_t len;
    int name[] = {CTL_KERN, KERN_OSTYPE};
    len = sizeof(osname);
    sysctl(name, 2, &osname, &len, NULL, 0);

/********       FETCH OS VERSION          *********/

    char osrelease[100];
    name[0] = CTL_KERN;
    name[1] = KERN_OSRELEASE;
    sysctl(name, 2, &osrelease, &len, NULL, 0);

	std::string osname_str(osname);
	std::string osrelease_str(osrelease);
	std::string osinfos = "MAC OS X El Capitan ";
	std::string osinfos2 = osname_str + " " + osrelease_str;

	std::string *str = new std::string("OS");
	std::string *str2 = new std::string(osinfos);
	std::string *str3 = new std::string(osinfos2);

	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));
	this->_fields.push_back(new Field(static_cast<void*>(str2), Field::STRING));
	this->_fields.push_back(new Field(static_cast<void*>(str3), Field::STRING));
}

OsInfosModule::OsInfosModule(OsInfosModule &other) :
	_fields(*(other.getFields()))
{
}

OsInfosModule::~OsInfosModule()
{
}

OsInfosModule	&OsInfosModule::operator=(OsInfosModule &other)
{
	this->_fields = *(other.getFields());
	return *this;
}

void				OsInfosModule::update()
{

}

std::vector<Field*>	*OsInfosModule::getFields()
{
	return &(this->_fields);
}
