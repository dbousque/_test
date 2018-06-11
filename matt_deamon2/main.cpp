

#include "matt_daemon.hpp"

Tintin_reporter	*g_reporter;
int				g_server_fd;
int				g_lock_file_fd;

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
		return (-1);
	}
	lock_file_fd = open(filename, O_CREAT, S_IRWXU);
	if (lock_file_fd < 0)
	{
		sprintf(buf, "Error, could not create %s", filename);
		reporter.log(buf, ERROR);
		return (-1);
	}
	if (flock(lock_file_fd, LOCK_EX | LOCK_NB) < 0)
	{
		sprintf(buf, "Error, %s already locked", filename);
		reporter.log(buf, ERROR);
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

int		main(int argc, char **argv)
{
	int		pid;
	char	buf[70];
	int		log_file_fd;

	(void)argc;
	(void)argv;
	g_lock_file_fd = -1;
	log_file_fd = -1;
	g_server_fd = -1;
	if (geteuid() != 0)
	{
		std::cout << "Sorry, you must be root to run me" << std::endl;
		return (0);
	}
	log_file_fd = open("/var/log/matt_daemon.log", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (log_file_fd < 0)
	{
		std::cout << "Could not open/create matt_daemon.log" << std::endl;
		return (0);
	}
	if (!(g_reporter = new Tintin_reporter(log_file_fd)))
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
	if (!g_reporter->log((char*)"Entering daemon mode", INFO))
		return (exit_daemon_main());
	pid = fork();
	if (pid < 0)
	{
		g_reporter->log((char*)"fork error", ERROR);
		return (exit_daemon_main());
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
		return (exit_daemon_main());
	}
	if (chdir("/") < 0)
	{
		g_reporter->log((char*)"chdir error", ERROR);
		return (exit_daemon_main());
	}
	sprintf(buf, "We are now a daemon with PID %d ", getpid());
	if (!g_reporter->log(buf, INFO))
		return (exit_daemon_main());
	signal(SIGKILL, signal_handler);
	run_server(*g_reporter, g_server_fd, g_lock_file_fd);
	return (0);
}