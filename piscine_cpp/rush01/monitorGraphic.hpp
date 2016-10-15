#ifndef MONITOR_GRAPHIC_HPP
# define MONITOR_GRAPHIC_HPP

#include <SFML/Mouse.hpp>
#include "IMonitorDisplay.hpp"
#include <iostream>
#include <string>

class monitorGraphic : public IMonitorDisplay {

public:
    monitorGraphic( void );
    monitorGraphic( monitorGraphic const & src );
    ~monitorGraphic( void );
    monitorGraphic &          operator=( monitorGraphic const & rhs );

private:
	IMonitorModule				*modules;

};

std::ostream &      operator<<( std::ostream & o, monitorGraphic const & i );

#endif