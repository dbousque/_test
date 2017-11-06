

#include "ft_irc.h"

void	log_start(t_log_mode mode)
{
	time_t		t;
	struct tm	tm;

	t = time(NULL);
	tm = *localtime(&t);
	if (mode == INFO)
		printf("\033[1;33m");
	if (mode == DEBUG)
		printf("\033[1;34m");
	if (mode == ERROR)
		printf("\033[0;31m");
	printf("%d-%02d-%02d %02d:%02d:%02d | ", tm.tm_year + 1900, tm.tm_mon + 1,
								tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void	log_end(t_log_mode mode)
{
	printf("\033[0m\n");
}