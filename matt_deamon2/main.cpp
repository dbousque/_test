

#include "matt_daemon.hpp"

Tintin_reporter	*g_reporter;
int				g_server_fd;
int				g_lock_file_fd;

bool	string_eq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (true);
	return (false);
}

int		get_lock(Tintin_reporter &reporter, char *filename)
{
	int		lock_file_fd;
	char	buf[100];

	lock_file_fd = open(filename, O_RDONLY);
	if (lock_file_fd >= 0)
	{
		close(lock_file_fd);
		sprintf(buf, "Error, %s already locked", filename);
		reporter.log(buf, ERROR);
		std::cout << buf << std::endl;
		return (-1);
	}
	lock_file_fd = open(filename, O_CREAT, S_IRWXU);
	if (lock_file_fd < 0)
	{
		sprintf(buf, "Error, could not create %s", filename);
		reporter.log(buf, ERROR);
		std::cout << buf << std::endl;
		return (-1);
	}
	if (flock(lock_file_fd, LOCK_EX | LOCK_NB) < 0)
	{
		sprintf(buf, "Error, %s already locked", filename);
		reporter.log(buf, ERROR);
		std::cout << buf << std::endl;
		close(lock_file_fd);
		return (-1);
	}
	return (lock_file_fd);
}

void	signal_handler(int signal)
{
	(void)signal;
	g_reporter->log((char*)"Quitting due to signal", INFO);
	exit_daemon(*g_reporter, g_server_fd, g_lock_file_fd);
}

int		exit_daemon_main(void)
{
	exit_daemon(*g_reporter, g_server_fd, g_lock_file_fd);
	return (0);
}

bool	exit_daemon_launch(void)
{
	exit_daemon(*g_reporter, g_server_fd, g_lock_file_fd);
	return (false);
}

bool	launch_daemon(void)
{
	int		pid;
	char	buf[70];

	if (!g_reporter->log((char*)"Entering daemon mode", INFO))
		return (exit_daemon_launch());
	pid = fork();
	if (pid < 0)
	{
		g_reporter->log((char*)"fork error", ERROR);
		return (exit_daemon_launch());
	}
	if (pid > 0)
	{
		std::cout << "Launched daemon, parent process exiting" << std::endl;
		return (0);
	}
	// create new session, so that we are detached from the calling context
	if (setsid() == (pid_t)-1)
	{
		g_reporter->log((char*)"setsid error", ERROR);
		return (exit_daemon_launch());
	}
	if (chdir("/") < 0)
	{
		g_reporter->log((char*)"chdir error", ERROR);
		return (exit_daemon_launch());
	}
	sprintf(buf, "We are now a daemon with PID %d ", getpid());
	if (!g_reporter->log(buf, INFO))
		return (exit_daemon_launch());
	return (true);
}

int		main(int argc, char **argv)
{
	int			log_file_fd;
	bool		foreground_mode;
	struct stat	st;

	foreground_mode = false;
	if (argc >= 2 && string_eq(argv[1], (char*)"-foreground"))
	{
		printf("Foreground mode activated\n");
		foreground_mode = true;
	}
	g_lock_file_fd = -1;
	log_file_fd = -1;
	g_server_fd = -1;
	if (geteuid() != 0)
	{
		std::cout << "Sorry, you must be root to run me" << std::endl;
		return (0);
	}
	if (stat("/var/log/matt_daemon", &st) == -1)
		mkdir("/var/log/matt_daemon", S_IRWXU);
	log_file_fd = open("/var/log/matt_daemon/matt_daemon.log", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (log_file_fd < 0)
	{
		std::cout << "Could not open/create matt_daemon.log" << std::endl;
		return (0);
	}
	if (!(g_reporter = new Tintin_reporter(log_file_fd, foreground_mode)))
	{
		std::cout << "Could not create Tintin_reporter" << std::endl;
		return (0);
	}
	if (!g_reporter->log((char*)"Started", INFO))
		return (exit_daemon_main());
	g_lock_file_fd = get_lock(*g_reporter, (char*)"/var/lock/matt_daemon.lock");
	if (g_lock_file_fd < 0)
		return (exit_daemon_main());
	if (!g_reporter->log((char*)"Creating server", INFO))
		return (exit_daemon_main());
	g_server_fd = create_server(4242);
	if (g_server_fd < 0)
	{
		g_reporter->log((char*)"Could not open server on port 4242", ERROR);
		return (exit_daemon_main());
	}
	if (!foreground_mode && !launch_daemon())
		return (0);

	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGTRAP, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGBUS, signal_handler);
	signal(SIGFPE, signal_handler);
	// not SIGKILL (9) - kills
	signal(SIGUSR1, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGPIPE, signal_handler);
	signal(SIGALRM, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGSTKFLT, signal_handler);
	signal(SIGCHLD, signal_handler);
	signal(SIGCONT, signal_handler);
	// not SIGSTOP (19) - not affected
	signal(SIGTSTP, signal_handler);
	signal(SIGTTIN, signal_handler);
	signal(SIGTTOU, signal_handler);
	signal(SIGURG, signal_handler);
	signal(SIGXCPU, signal_handler);
	signal(SIGXFSZ, signal_handler);
	signal(SIGVTALRM, signal_handler);
	signal(SIGPROF, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGPOLL, signal_handler);
	signal(SIGPWR, signal_handler);
	signal(SIGSYS, signal_handler);
	// from 32 to 64 included, kernel real-time signals

	run_server(*g_reporter, g_server_fd, g_lock_file_fd);
	return (0);
}