

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include <unistd.h>

int		TARGET_FRAMERATE = 15;
size_t	TO_WAIT_PER_FRAME = 1000 / TARGET_FRAMERATE;

void erase (int y, int x) {
	mvaddch(y, x, '#');
}

bool	handle_key(int ch)
{
	if(ch == KEY_LEFT) {
		erase(row, col);
		col = col - 1;
		mvaddch(row, col, main_char);
		refresh();
	}
	else if(ch == KEY_RIGHT) {
		erase(row, col);
		col = col + 1;
		mvaddch(row, col, main_char);
		refresh();
	}
	else if(ch == KEY_UP) {
		erase(row, col);
		row = row - 1;
		mvaddch(row, col, main_char);
		refresh();
	}
	else if(ch == KEY_DOWN) {
		erase(row, col);
		row = row + 1;
		mvaddch(row, col, main_char);
		refresh();
	}
	else if(ch == 'q' || ch == 'Q')
		return false;
	return true;
}

void game_loop(char main_char, int row, int col) {
	clock_t	start;
	clock_t	end;
	int		ch;

	ch = -1;
	// Check if the user wishes to play the game
	if(ch == 'q' || ch =='Q') return;

	// Show the main character on the screen
	mvaddch(row, col, main_char);
	refresh();

	for(;;) {
		start = clock();
		if (!handle_key(ch, row, col, main_char))
			break ;
		end = clock();
		if (start + TO_WAIT_PER_FRAME > end)
		{
			timeout(start + TO_WAIT_PER_FRAME - end);
			ch = getch();
		}
	}
}

int main(void)
{
	// Define main character symbol and initial position
	int row = 10, col = 10;
	char main_char = '@';

	// Start ncurses
	initscr();
	keypad(stdscr, TRUE);
	// Print a welcome message on screen
	printw("Welcome to the my game.");
	// Wait until the user press a key
	timeout(1000);
	int ch = getch();
	// Clear the screen
	clear();	
	// Start the game loop
	game_loop(main_char, row, col);
	// Clear ncurses data structures
	endwin();
	return 0;
}