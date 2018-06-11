

#include "matt_daemon.hpp"

void	exit_daemon(Tintin_reporter &reporter, int server_fd, int lock_file_fd)
{
	if (server_fd >= 0)
		close(server_fd);
	delete &reporter;
	if (lock_file_fd >= 0)
	{
		flock(lock_file_fd, LOCK_UN | LOCK_NB);
		close(lock_file_fd);
		unlink("/var/lock/matt_daemon.lock");
	}
}