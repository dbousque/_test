

#include "RamModule.hpp"
#include <sys/types.h>
#include <sys/sysctl.h>

#include <mach/mach.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int		get_used_memory()
{
	vm_statistics64_data_t	vm_stat;
	long long				used_pages;
	mach_port_t				myHost;
	unsigned int			count = sizeof(vm_stat) / sizeof(natural_t);

	myHost = mach_host_self();
	host_statistics64(myHost, HOST_VM_INFO64, (host_info64_t)(&vm_stat), &count);
	used_pages = (int64_t)vm_stat.active_count
			+ (int64_t)vm_stat.inactive_count
			+ (int64_t)vm_stat.wire_count;
	return (used_pages * getpagesize()) / (1024 * 1024);
}

RamModule::RamModule()
{
    int 		mib[2];
    int64_t		physical_memory;
    std::string	*physical = new std::string("");
    size_t		length;
    std::string	*title = new std::string("RAM");
    std::string	*total = new std::string("Total :");
    std::string	*total_avaiable = new std::string("Used :");
    std::string	*avaiable = new std::string("");

    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    *physical = std::to_string(physical_memory / (1024 * 1024)) + " MB";
    *avaiable = std::to_string(get_used_memory()) + " MB";
    this->_fields.push_back(new Field(static_cast<void*>(title), Field::MODULE_TITLE));
    this->_fields.push_back(new Field(static_cast<void*>(total), Field::STRING));
    this->_fields.push_back(new Field(static_cast<void*>(physical), Field::STRING));
    this->_fields.push_back(new Field(static_cast<void*>(total_avaiable), Field::STRING));
    this->_fields.push_back(new Field(static_cast<void*>(avaiable), Field::STRING));
}

RamModule::RamModule(RamModule &other) :
	_fields(*(other.getFields()))
{
}

RamModule::~RamModule()
{
}

RamModule	&RamModule::operator=(RamModule &other)
{
	this->_fields = *(other.getFields());
	return *this;
}

void	RamModule::update()
{
	std::string	*avaiable = new std::string("");

	*avaiable = std::to_string(get_used_memory()) + " MB";
	delete this->_fields[4];
	this->_fields[4] = new Field(static_cast<void*>(avaiable), Field::STRING);
}

std::vector<Field*>	*RamModule::getFields()
{
	return &(this->_fields);
}