#include "CpuModule.hpp"
#include <stdlib.h>

CpuModule::CpuModule()
{
/********       FETCH NB OF CPUs          *********/

	int nbcpu;
    size_t len;
    
    int name[] = {CTL_HW, HW_NCPU};
    len = sizeof(nbcpu);
    sysctl(name, 2, &nbcpu, &len, NULL, 0);

/********       FETCH MODEL OF CPUs          *********/

	char modelname[100] = {0};

	name[0] = CTL_HW;
	name[1] = HW_MODEL;
	len = sizeof(modelname);
	sysctl(name, 2, &modelname, &len, NULL, 0);

	std::string	*str = new std::string("CPU");
	std::string *str2 = new std::string(modelname);
	std::string *str3 = new std::string(std::to_string(nbcpu) + " CPUs");
	std::string *str4 = new std::string("Clock speed :");
	
	float 	*usage = new float(this->_getCPULoad() * 100);

    std::string *str6 = new std::string("Usage :");
    //std::string *str5 = new std::string(this->_getCPUActivity() + "%");
    int		*activity = new int;

    Field	*tmp_field = new Field(static_cast<void*>(activity), Field::GRAPH_INT);
    tmp_field->setId(3);
    *activity = static_cast<int>(this->_getCPUActivity() * 100);
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE));	 	// 0
	this->_fields.push_back(new Field(static_cast<void*>(str2), Field::STRING));			// 1
	this->_fields.push_back(new Field(static_cast<void*>(str3), Field::STRING));			// 2
	this->_fields.push_back(new Field(static_cast<void*>(str4), Field::STRING));			// 3
	this->_fields.push_back(new Field(static_cast<void*>(usage), Field::FLOATING));			// 4
	this->_fields.push_back(new Field(static_cast<void*>(str6), Field::STRING));			// 5
	this->_fields.push_back(tmp_field);			// 6
	delete usage;
}

CpuModule::CpuModule(CpuModule &other) :
	_fields(*(other.getFields()))
{
}

CpuModule::~CpuModule()
{
}

CpuModule	&CpuModule::operator=(CpuModule &other)
{
	this->_fields = *(other.getFields());
	return *this;
}

void				CpuModule::update()
{
	float *usage = new float(this->_getCPULoad() * 100);
	Field *tmp = new Field(static_cast<void*>(usage), Field::FLOATING);
	delete this->_fields[4];
    this->_fields[4] = tmp;

    int		*activity = new int;
    *activity = static_cast<int>(this->_getCPUActivity() * 100);
    //std::string *str = new std::string(this->_getCPUActivity() + "%");
    Field *tmp3 = new Field(static_cast<void*>(activity), Field::GRAPH_INT);
    tmp3->setId(3);
    delete this->_fields[6];
    this->_fields[6] = tmp3;

}

std::vector<Field*>	*CpuModule::getFields()
{
	return &(this->_fields);
}

float 				CpuModule::_getCPULoad() {
	float sysLoadPercentage;
	host_cpu_load_info_data_t cpuinfo;
	mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, reinterpret_cast<host_info_t>(&cpuinfo), &count) == KERN_SUCCESS)
	{
		unsigned long long totalTicks = 0;
		for(int i = 0; i < CPU_STATE_MAX; i++) {
			totalTicks += cpuinfo.cpu_ticks[i];
		}
		sysLoadPercentage = this->_calculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
	}
	else
		return -1.0f;
	return sysLoadPercentage;
}

float			CpuModule::_calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	unsigned long long totalTicksSinceLastTime = totalTicks - this->_previousTotalTicks;
	unsigned long long idleTicksSinceLastTime  = idleTicks - this->_previousIdleTicks;
	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? (static_cast<float>(idleTicksSinceLastTime)) / totalTicksSinceLastTime : 0);
	this->_previousTotalTicks = totalTicks;
	this->_previousIdleTicks  = idleTicks;
	return ret;
}

int			CpuModule::_getCPUActivity() {
	char buffer[128];
    std::string result = "";
    FILE* pipe = popen("top -l 1 | grep -i 'Cpu' |  cut -d ' ' -f 3", "r");
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return atoi(result.c_str());
}