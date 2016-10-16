#ifndef MONITOR_GRAPHIC_HPP
# define MONITOR_GRAPHIC_HPP

//#include <SFML/Mouse.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "IMonitorDisplay.hpp"
#include "Field.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

class monitorGraphic : public IMonitorDisplay
{
	public:
	    monitorGraphic(sf::RenderWindow &window);
	    monitorGraphic(monitorGraphic const &src);
	    virtual ~monitorGraphic( void );
	    monitorGraphic &          operator=( monitorGraphic const & rhs );

		void        displayModules(std::vector<IMonitorModule*> modules);
		void        eventHandler();
		void        optionsHandler();
		void        closeAll();
		void        init();
		sf::RenderWindow	&getWindow() const;

	private:
		monitorGraphic();
		void        _displayTitle();
		void        _displayRectangle(int start_x, int start_y, int width, int height);
		int			_actualDisplayGraph(int val, std::list<int> &graph, int display_y);
		int			_displayGraph(int val, int graph_id, int display_y);
		int			_displayField(Field &field, int display_h);
		int         _displayModule(IMonitorModule &module);

		sf::RenderWindow				&_window;
		sf::Font						_title_font;
		sf::Font						_text_font;
		int         					_current_x;
		int         					_current_y;
		std::vector<std::list<int> >	_graphs;
};

#endif
