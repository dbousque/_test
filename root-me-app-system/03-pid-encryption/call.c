#include <unistd.h>
#include <stdio.h>
#include <crypt.h>

int		main(void)
{
	pid_t	pid = fork();
	if (pid == 0)
	{
		char	pid[16];
		snprintf(pid, sizeof(pid), "%i", getpid());
		char	*args[3] = {"ch21", crypt(pid, "$1$awesome"), NULL};
		execv("/challenge/cryptanalyse/ch21/ch21", args);
	}
	else
		wait(NULL);
	return (0);
}
