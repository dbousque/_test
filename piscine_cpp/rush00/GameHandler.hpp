

#ifndef GAMEHANDLER_H
# define GAMEHANDLER_H

#include "RetroWorld.hpp"
#include "Config.hpp"
#include <ctime>
#include <ncurses.h>

class GameHandler
{
	public:
		GameHandler();
		GameHandler(GameHandler &other);
		~GameHandler();

		GameHandler			&operator=(GameHandler &other);
		void				mainLoop();
		RetroWorld			&getRetro();

	private:
		bool				_handleKey(int ch);
		void				_showContainer();
		RetroWorld			&_retro;
		static void			_init_ncurses();
};

#endif