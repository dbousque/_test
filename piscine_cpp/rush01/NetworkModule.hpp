#ifndef NETWORKMODULE_H
# define NETWORKMODULE_H

# define OCTETS		'o'
# define PACKETS	'p'

# include <iostream>
# include <map>
# include <utility>
#include <net/route.h>
#include <net/if.h>
#include <sys/sysctl.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <string>

#include "IMonitorModule.hpp"


class NetworkModule : public IMonitorModule
{
	public:
		struct Data {
			std::string		ip;
			std::map<char, std::pair<std::pair<long long, long long>, std::pair<long long, long long> > >		net;
		};
		NetworkModule();
		NetworkModule(NetworkModule &other);
		virtual ~NetworkModule();

		NetworkModule	&operator=(NetworkModule &other);
		Data			getData(void) const;

		void				update();
		std::vector<Field*>	*getFields();

	private:
		std::vector<Field*>	_fields;
		Data			_data;
		int64_t 		_prev_ibytes;
		int64_t 		_prev_obytes;
};

#endif