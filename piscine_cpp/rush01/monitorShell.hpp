#ifndef MONITOR_SHELL_HPP
# define MONITOR_SHELL_HPP

#include "IMonitorDisplay.hpp"
#include <ncurses.h>
#include <string>

class monitorShell : public IMonitorDisplay
{
	public:
		monitorShell( void );
		monitorShell( monitorShell const & src );
		virtual ~monitorShell( void );
		monitorShell	&operator=( monitorShell const & rhs );

		void		displayModules(std::vector<IMonitorModule*> modules);
		void		eventHandler();
		void		optionsHandler();
		void		closeAll();
		void		init();

	private:
		std::string	_getFieldStr(std::vector<Field*> &fields, int i);
		void		_updateWinSize();
		void		_displayTitle();
		void		_displayRectangle(int start_x, int start_y, int width, int height);
		void		_displayModule(IMonitorModule &module);

		int			_win_width;
		int			_win_height;
		int			_current_x;
		int			_current_y;
};

#endif