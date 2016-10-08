

#include "GameHandler.hpp"
#include <iostream>

int		TARGET_FRAMERATE = 15;
size_t	TO_WAIT_PER_FRAME = 1000 / TARGET_FRAMERATE;

void		GameHandler::_init_ncurses()
{
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	printw("Welcome to the my game.");
	timeout(1000);
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
	clock_t	start;
	clock_t	end;
	int		ch;

	this->_showContainer();
	ch = -1;
	for(;;) {
		start = clock();
		if (!this->_handleKey(ch))
			break ;
		end = clock();
		if (start + TO_WAIT_PER_FRAME > end)
		{
			timeout(start + TO_WAIT_PER_FRAME - end);
			ch = getch();
		}
	}
}