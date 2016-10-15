#ifndef I_MONITOR_DISPLAY_HPP
# define I_MONITOR_DISPLAY_HPP

#include <vector>
#include "IMonitorModule.hpp"

class IMonitorDisplay {

public:
    virtual ~IMonitorDisplay( void ) {}
    virtual void	displayModules(std::vector<IMonitorModule*> modules) = 0;
    virtual void	eventHandler() = 0;
    virtual void	optionsHandler() = 0;
    virtual void	closeAll() = 0;
    virtual void	init() = 0;

};

#endif