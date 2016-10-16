#include "NetworkModule.hpp"

NetworkModule::NetworkModule() : _prev_ibytes(0), _prev_obytes(0)
{
	this->update();
	struct ifaddrs * ifAddrStruct = NULL;
    struct ifaddrs * ifa = NULL;
    void * tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET)
		{ // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((reinterpret_cast<struct sockaddr_in *>(ifa->ifa_addr)))->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			if (strcmp(addressBuffer, "127.0.0.1"))
			{
				this->_data.ip = ifa->ifa_name;
				this->_data.ip.append(" : ").append(addressBuffer);
			}
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);

    std::string *str = new std::string("NETWORK");
	std::string *str3 = new std::string("Data sent :");
	std::string *str4 = new std::string("Data received :");

	int 	*usage = new int;
	*usage = _data.net[OCTETS].first.second;
	int 	*usage2 = new int;
	*usage2 = _data.net[OCTETS].second.second;

	Field	*tmp1;
	Field	*tmp2;

	tmp1 = new Field(static_cast<void*>(usage), Field::GRAPH_INT);
	tmp1->setId(1);
	tmp2 = new Field(static_cast<void*>(usage2), Field::GRAPH_INT);
	tmp2->setId(2);
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::MODULE_TITLE)); //0
	this->_fields.push_back(new Field(static_cast<void*>(str3), Field::STRING));	//2
	this->_fields.push_back(tmp1);	//3 <- int
	this->_fields.push_back(new Field(static_cast<void*>(str4), Field::STRING));	//4
	this->_fields.push_back(tmp2);	//5 <- int

}

NetworkModule::NetworkModule(NetworkModule &other) :
	_fields(*(other.getFields()))
{
}

NetworkModule::~NetworkModule()
{
}

NetworkModule	&NetworkModule::operator=(NetworkModule &other)
{
	this->_fields = *(other.getFields());
	return *this;
}

NetworkModule::Data		NetworkModule::getData(void) const {
	return this->_data;
}

void				NetworkModule::update()
{

	short network_layer;
	short link_layer;
	int mib[6];
	char  *lim, *next;
	size_t len;
	struct if_msghdr *ifm;

	int64_t ibytes = 0;
	int64_t obytes = 0;

	static_cast<void>(network_layer);
	mib[0]= CTL_NET;// networking subsystem
	mib[1]= PF_ROUTE;// type of information
	mib[2]= 0;// protocol (IPPROTO_xxx)
	mib[3]= 0;// address family
	mib[4]= NET_RT_IFLIST2;// operation
	mib[5]= 0;
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return ;

	char		buf[len];

	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0)
	{
		return ;
	}
	lim = buf + len;
	for (next = buf; next < lim; )
	{
		network_layer = link_layer = 0;
		ifm = reinterpret_cast<struct if_msghdr *>(next);
		next += ifm->ifm_msglen;

		if (ifm->ifm_type == RTM_IFINFO2)
		{
			struct if_msghdr2 *if2m = reinterpret_cast<struct if_msghdr2 *>(ifm);

			if(if2m->ifm_data.ifi_type!=18)
			{ /* do not count loopback traffic */

				obytes   += if2m->ifm_data.ifi_obytes;
				ibytes   += if2m->ifm_data.ifi_ibytes;
			}
		}
	}

	int64_t delta_obytes = obytes - this->_prev_obytes;
	int64_t delta_ibytes = ibytes - this->_prev_ibytes;


	this->_prev_ibytes = ibytes;
	this->_prev_obytes = obytes;

	this->_data.net[OCTETS].first.second = static_cast<long long>(delta_ibytes);
	this->_data.net[OCTETS].second.second = static_cast<long long>(delta_obytes);

	if (this->_fields.size() > 0) {
		int 	*usage = new int;
		*usage = _data.net[OCTETS].first.second;
		Field *tmp = new Field(static_cast<void*>(usage), Field::GRAPH_INT);
		tmp->setId(1);
		delete this->_fields[2];
		this->_fields[2] = tmp;
		

		int 	*usage2 = new int;
		*usage2 = _data.net[OCTETS].second.second;
		Field *tmp1 = new Field(static_cast<void*>(usage2), Field::GRAPH_INT);
		tmp1->setId(2);
		delete this->_fields[4];
		this->_fields[4] = tmp1;
	}
}


std::vector<Field*>	*NetworkModule::getFields()
{
	return &(this->_fields);
}
