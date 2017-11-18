

#include <unistd.h>
#include <ncurses.h>

int		main(void)
{
	WINDOW	*users_win;
	WINDOW	*input_win_container;
	WINDOW	*input_win;
	WINDOW	*text_win_container;
	WINDOW	*text_win;
	WINDOW	*info_win;

	initscr();
	start_color();

	curs_set(2);

	refresh();

	users_win = newwin(LINES - 3, 20, 0, COLS - 20);
	box(users_win, 0, 0);
	wrefresh(users_win);

	input_win_container = newwin(3, COLS, LINES - 3, 0);
	box(input_win_container, 0, 0);
	wrefresh(input_win_container);

	input_win = newwin(1, COLS - 3, LINES - 2, 2);
	wrefresh(input_win);

	text_win_container = newwin(LINES - 9, COLS - 21, 6, 0);
	box(text_win_container, 0, 0);
	wrefresh(text_win_container);

	text_win = newwin(LINES - 13, COLS - 24, 9, 2);
	wrefresh(text_win);

	info_win = newwin(6, COLS - 21, 0, 0);
	box(info_win, 0, 0);
	wrefresh(info_win);

	wmove(users_win, 1, 2);
	wprintw(users_win, "USERS ON SERVER");
	wrefresh(users_win);

	wmove(info_win, 1, 2);
	wprintw(info_win, "INFO");
	wrefresh(info_win);

	wmove(text_win_container, 1, 2);
	wprintw(text_win_container, "SERVER OUTPUT");
	wrefresh(text_win_container);

	wmove(input_win, 0, 0);
	wrefresh(input_win);

	scrollok(text_win, TRUE);
	while (1)
	{
		char	str[100];

		int ret = read(0, str, 99);
		str[ret] = '\0';
		if (str[0] == 27)
			break ;
		wprintw(input_win, str);
		if (str[0] == '\r')
		{
			wprintw(text_win, "hello guys how do you do doing there\n");
			wrefresh(text_win);
			wclear(input_win);
			wmove(input_win, 0, 0);
		}
		wrefresh(input_win);
	}

	endwin();
	return (0);
}
