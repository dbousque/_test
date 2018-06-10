

#include "matt_daemon.hpp"

Tintin_reporter	*g_reporter;

int		get_lock(char *filename)
{
	int		lock_file_fd;

	lock_file_fd = open(filename, O_RDONLY);
	if (lock_file_fd >= 0)
	{
		close(lock_file_fd);
		std::cout << filename << " already exists" << std::endl;
		return (-1);
	}
	lock_file_fd = open(filename, O_CREAT, S_IRWXU);
	if (lock_file_fd < 0)
	{
		std::cout << "Could not create " << filename << std::endl;
		return (-1);
	}
	if (flock(lock_file_fd, LOCK_EX | LOCK_NB) < 0)
	{
		std::cout << "Could not get lock on " << filename << ", a process is probably already opened" << std::endl;
		close(lock_file_fd);
		return (-1);
	}
	return (lock_file_fd);
}

int		fatal_error(char *msg, int lock_file_fd, int log_file_fd, int server_fd)
{
	std::cout << msg << std::endl;
	flock(lock_file_fd, LOCK_UN | LOCK_NB);
	close(lock_file_fd);
	if (unlink("/var/lock/matt_daemon.lock") < 0)
		std::cout << "Could not delete /var/lock/matt_daemon.lock" << std::endl;
	if (log_file_fd >= 0)
		close(log_file_fd);
	if (server_fd >= 0)
		close(server_fd);
	return (0);
}

void	signal_handler(int signal)
{
	(void)signal;
	delete g_reporter;
}

int		main(int argc, char **argv)
{
	int				lock_file_fd;
	int				log_file_fd;
	int				server_fd;
	int				pid;

	(void)argc;
	(void)argv;
	lock_file_fd = -1;
	log_file_fd = -1;
	server_fd = -1;
	if (geteuid() != 0)
	{
		std::cout << "Sorry, you must be root to run me" << std::endl;
		return (0);
	}
	lock_file_fd = get_lock((char*)"/var/lock/matt_daemon.lock");
	if (lock_file_fd < 0)
		return (0);
	log_file_fd = open("/var/log/matt_daemon.log", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (log_file_fd < 0)
		return (fatal_error((char*)"Could not open/create matt_daemon.log", lock_file_fd, log_file_fd, server_fd));
	server_fd = create_server(4242);
	if (server_fd < 0)
		return (fatal_error((char*)"Could not open server on port 4242", lock_file_fd, log_file_fd, server_fd));
	pid = fork();
	if (pid < 0)
		return (fatal_error((char*)"fork error", lock_file_fd, log_file_fd, server_fd));
	if (pid > 0)
	{
		std::cout << "Launching daemon, parent process exiting" << std::endl;
		return (0);
	}
	// create new session, so that we are detached from the calling context
	if (setsid() == (pid_t)-1)
		return (fatal_error((char*)"setsid error", lock_file_fd, log_file_fd, server_fd));
	if (chdir("/") < 0)
		return (fatal_error((char*)"chdir error", lock_file_fd, log_file_fd, server_fd));
	g_reporter = new Tintin_reporter(lock_file_fd, log_file_fd, server_fd);
	signal(SIGKILL, signal_handler);
	delete g_reporter;
	return (0);
}