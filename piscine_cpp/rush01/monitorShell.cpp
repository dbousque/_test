

#include "monitorShell.hpp"
#include <fstream>

monitorShell::monitorShell()
{
	this->init();
}

monitorShell::monitorShell(monitorShell const &)
{
	this->init();
}

monitorShell::~monitorShell()
{
	this->closeAll();
}

monitorShell	&monitorShell::operator=(monitorShell const &)
{
	return *this;
}

void	monitorShell::displayModules(std::vector<IMonitorModule*> modules)
{
	this->_updateWinSize();
	int		nb_mod_per_line = 1;
	while (nb_mod_per_line < static_cast<int>(modules.size()) && ((nb_mod_per_line - 2) * 35 + 80) + 35 <= this->_win_width)
		nb_mod_per_line++;
	this->_current_x = 3 + (this->_win_width - (nb_mod_per_line * 35)) / 2;
	this->_current_y = 9;
	this->_displayTitle();
	for (std::vector<IMonitorModule*>::iterator iter = modules.begin(); iter != modules.end(); iter++)
	{
		this->_displayModule(**iter);
		if (this->_current_x + 70 > this->_win_width)
		{
			this->_current_x = 3 + (this->_win_width - (nb_mod_per_line * 35)) / 2;
			this->_current_y += 14;
		}
		else
			this->_current_x += 35;
	}
	refresh();
}

void	monitorShell::eventHandler()
{

}

void	monitorShell::optionsHandler()
{

}

void	monitorShell::closeAll()
{
	endwin();
}

void	monitorShell::init()
{
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	start_color();
	attron(A_BOLD);
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
	clear();
}

std::string	monitorShell::_getFieldStr(std::vector<Field*> &fields, int i)
{
	if (fields[i]->getType() == Field::STRING)
		return *(static_cast<std::string*>(fields[i]->getData()));
	if (fields[i]->getType() == Field::INTEGER)
		return std::to_string(*(static_cast<int*>(fields[i]->getData())));
	if (fields[i]->getType() == Field::INTEGER_PERCENT)
		return std::to_string(*(static_cast<int*>(fields[i]->getData()))) + "%%";
	return "";
}

void	monitorShell::_updateWinSize()
{
	getmaxyx(stdscr, this->_win_height, this->_win_width);
}

void	monitorShell::_displayTitle()
{
	attron(COLOR_PAIR(6));
	std::string	title[] = {
		std::string("   __ _            _             _ _           "),
		std::string("  / _| |          | |           | | |          "),
		std::string(" | |_| |_     __ _| | ___ __ ___| | |_ __ ___  "),
		std::string(" |  _| __|   / _` | |/ / '__/ _ \\ | | '_ ` _ \\ "),
		std::string(" | | | |_   | (_| |   <| | |  __/ | | | | | | |"),
		std::string(" |_|  \\__|   \\__, |_|\\_\\_|  \\___|_|_|_| |_| |_|"),
		std::string("       ______ __/ |                            "),
		std::string("      |______|___/                             ")
	};

	for (int i = 0; i < 8; i++)
	{
		for (size_t x = 0; x < title[i].length(); x++)
			mvaddch(i, (this->_win_width / 2 - (title[i].length() / 2)) + x, title[i][x]);
	}
	attroff(COLOR_PAIR(6));
}

void	monitorShell::_displayRectangle(int start_x, int start_y, int width, int height)
{
	for (int i = 0; i < width; i++)
		mvaddch(start_y, start_x + i, '_');
	for (int i = 0; i < width; i++)
		mvaddch(start_y + height, start_x + i, '_');
	for (int i = 1; i < height + 1; i++)
		mvaddch(start_y + i, start_x - 1, '|');
	for (int i = 1; i < height + 1; i++)
		mvaddch(start_y + i, start_x + width, '|');
}

void	monitorShell::_displayModule(IMonitorModule &module)
{
	std::vector<Field*>	&fields = *(module.getFields());
	std::string			*title = static_cast<std::string*>(fields[0]->getData());
	std::vector<std::string>	fields_strs;

	this->_displayRectangle(this->_current_x, this->_current_y, 30, 12);
	this->_displayRectangle(this->_current_x, this->_current_y, 30, 3);
	move(this->_current_y + 2, this->_current_x + 15 - (title->length() / 2));
	attron(COLOR_PAIR(4));
	if (this->_current_y + 2 < this->_win_height)
		printw((*title).c_str());
	attroff(COLOR_PAIR(4));
	for (size_t i = 1; i < fields.size(); i++)
	{
		std::string		tmp = this->_getFieldStr(fields, i);
		if (tmp != "")
			fields_strs.push_back(tmp);
	}
	for (size_t i = 0; i < fields_strs.size(); i++)
	{
		int		text_y = this->_current_y + 3 + (10 / (fields_strs.size() + 1)) * (i + 1);
		int		text_x = this->_current_x + 15 - (fields_strs[i].length() / 2);
		move(text_y, text_x);
		if (text_y < this->_win_height)
			printw(fields_strs[i].c_str());
	}
}