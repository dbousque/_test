

#include "Tintin_reporter.hpp"

int		main(int argc, char **argv)
{
	int		lock_file_fd;
	int		log_file_fd;
	int		server_fd;

	(void)argc;
	(void)argv;
	if (geteuid() != 0)
	{
		std::cout << "Sorry, you must be root to run me" << std::endl;
		return (0);	
	}
	std::cout << "You are root !" << std::endl;
	lock_file_fd = open("/var/lock/matt_daemon.lock", O_CREAT, S_IRWXU);
	if (lock_file_fd < 0)
	{
		std::cout << "Could not open/create matt_daemon.lock" << std::endl;
		return (0);
	}
	if (flock(lock_file_fd, LOCK_EX | LOCK_NB) < 0)
	{
		std::cout << "Could not get lock on matt_daemon.lock, a matt_daemon process is probably already opened" << std::endl;
		close(lock_file_fd);
		return (0);
	}
	log_file_fd = open("/var/log/matt_daemon.log", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (log_file_fd < 0)
	{
		std::cout << "Could not open/create matt_daemon.log" << std::endl;
		flock(lock_file_fd, LOCK_UN | LOCK_NB);
		close(lock_file_fd);
		return (0);
	}
	server_fd = create_server(4242);
	if (server_fd == -1)
	{
		std::cout << "Could not open server on port 4242" << std::endl;
		flock(lock_file_fd, LOCK_UN | LOCK_NB);
		close(lock_file_fd);
		close(log_file_fd);
		return (0);
	}
	sleep(10);
	return (0);
}