#ifndef I_MONITOR_MODULE_HPP
# define I_MONITOR_MODULE_HPP

#include <vector>
#include "Field.hpp"

class IMonitorModule {

public:
    virtual ~IMonitorModule( void ) {}
    virtual void	update( void ) = 0;
    virtual std::vector<Field*>	*getFields() = 0;
};

#endif