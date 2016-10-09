

#include "GameHandler.hpp"
#include <iostream>
#include <sys/time.h>
#include <unistd.h>

int				TARGET_FRAMERATE = 60;
unsigned long	TO_WAIT_PER_FRAME = 1000 / TARGET_FRAMERATE;

unsigned long	getCurrentMillis()
{
	struct timeval	t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

void		GameHandler::_init_ncurses()
{
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	char	title[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
                                                                                     ____  _            _       \n\
                                                                                    | __ )| | __ _  ___| | __   \n\
                                                                                    |  _ \\| |/ _` |/ __| |/ /   \n\
                                                                                    | |_) | | (_| | (__|   <    \n\
                                                                                ___ |____/|_|\\__,_|\\___|_|\\_\\   \n\
                                                                               / _ \\ _ __ __ _ _ __   __ _  ___ \n\
                                                                              | | | | '__/ _` | '_ \\ / _` |/ _ \\\n\
                                                                              | |_| | | | (_| | | | | (_| |  __/\n\
                                                                               \\___/|_|  \\__,_|_| |_|\\__, |\\___|\n\
                                                                                                     |___/      ";
 	printw(title);
	timeout(1000);
	getch();
	printw("\n\n                                                                                      dbousque and gschroed");
	timeout(2100);
	getch();
	// Clear the screen
	clear();
}

GameHandler::GameHandler() :
	_retro(*(new RetroWorld))
{
	GameHandler::_init_ncurses();
}

GameHandler::GameHandler(GameHandler &other) :
	_retro(other.getRetro())
{
	GameHandler::_init_ncurses();
}

GameHandler::~GameHandler()
{
	delete &this->_retro;
	endwin();
}

GameHandler		&GameHandler::operator=(GameHandler &other)
{
	return *(new GameHandler(other));
}

RetroWorld		&GameHandler::getRetro()
{
	return this->_retro;
}

void	GameHandler::_showContainer()
{
	for (int i = 30; i < 160; i++)
		mvaddch(10, i, '_');
	for (int i = 30; i < 160; i++)
		mvaddch(57, i, '_');
	for (int i = 11; i < 58; i++)
		mvaddch(i, 29, '|');
	for (int i = 11; i < 58; i++)
		mvaddch(i, 160, '|');
	refresh();
}

bool	GameHandler::_handleKey(int ch)
{
	if (ch == KEY_LEFT)
		(this->_retro).characterLeft();
	else if (ch == KEY_RIGHT)
		this->_retro.characterRight();
	else if (ch == KEY_UP)
		this->_retro.characterUp();
	else if (ch == KEY_DOWN)
		this->_retro.characterDown();
	else if (ch == ' ')
		this->_retro.characterShoot();
	return true;
}

void	GameHandler::mainLoop()
{
	unsigned long	start;
	unsigned long	end;
	unsigned long	end2;
	int				ch;

	ch = -1;
	for(;;) {
		start = getCurrentMillis();
		if (!this->_handleKey(ch))
			break ;
		erase();
		this->_showContainer();
		this->_retro.updateVars();
		this->_retro.displayStuff();
		refresh();
		end = getCurrentMillis();
		if (start + TO_WAIT_PER_FRAME > end)
		{
			timeout(start + TO_WAIT_PER_FRAME - end);
			ch = getch();
			end2 = getCurrentMillis();
			if (end2 < start + TO_WAIT_PER_FRAME)
				usleep((TO_WAIT_PER_FRAME - (end2 - start)) * 1000);
		}
	}
}