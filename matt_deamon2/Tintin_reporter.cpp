

#include "Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter(int lock_file_fd, int log_file_fd, int server_fd) :
	_lock_file_fd(lock_file_fd),
	_log_file_fd(log_file_fd),
	_server_fd(server_fd),
	_failed_write(0)
{
	this->run_server();
}

void	Tintin_reporter::run_server(void)
{
	int		highest_fd;
	int		clients[MAX_NB_CLIENTS];
	int		nb_clients;
	int		nb_ready;
	fd_set	fds;
	int		i;

	nb_clients = 0;
	while (1)
	{
		FD_ZERO(&fds);
		FD_SET(_server_fd, &fds);
		highest_fd = _server_fd;
		i = 0;
		while (i < nb_clients)
		{
			if (clients[i] > highest_fd)
				highest_fd = clients[i];
			FD_SET(clients[i], &fds);
			i++;
		}
		nb_ready = select(highest_fd + 1, &fds, NULL, NULL, NULL);
		if (nb_ready == -1)
		{
			this->log((char*)"select error", ERROR);
			delete this;
			return ;
		}
		if (nb_ready > 0)
		{
			if (FD_ISSET(_server_fd, &fds))
			{
				if (!(this->accept_client(_server_fd, clients, &nb_clients)))
				{
					delete this;
					return ;
				}
				nb_ready--;
			}
			i = 0;
			while (i < nb_ready)
			{
				if (FD_ISSET(clients[i], &fds))
				{
					if (!(this->read_and_log_client_input(i, clients, &nb_clients)))
					{
						delete this;
						return ;
					}
				}
				i++;
			}
		}
	}
}

bool	Tintin_reporter::read_and_log_client_input(int i, int *clients, int *nb_clients)
{
	char	buf[512];
	int		ret;
	int		x;

	ret = read(clients[i], buf, 511);
	if (ret < 0)
	{
		if (!(this->log((char*)"Could not read client input", INFO)))
			return (false);
	}
	if (ret <= 0)
	{
		if (!(this->log((char*)"Closing client", INFO)))
			return (false);
		x = i;
		while (x < *nb_clients - 1)
		{
			clients[x] = clients[x + 1];
			x++;
		}
		(*nb_clients)--;
		return (true);
	}
	buf[ret] = '\0';
	if (!(this->log(buf, LOG)))
		return (false);
	if (ret == 5 && buf[0] == 'q' && buf[1] == 'u' && buf[2] == 'i' && buf[3] == 't' && buf[4] == '\n')
	{
		if (!(this->log((char*)"Closing client", INFO)))
			return (false);
		x = i;
		while (x < *nb_clients - 1)
		{
			clients[x] = clients[x + 1];
			x++;
		}
		(*nb_clients)--;
		return (true);
	}
	return (true);
}

bool	Tintin_reporter::accept_client(int server_fd, int *clients, int *nb_clients)
{
	struct sockaddr_in	sin;
	socklen_t			len;

	if (*nb_clients >= MAX_NB_CLIENTS)
	{
		if (!(this->log((char*)"Could not accept new client, too many clients connected", INFO)))
			return (false);
		return (true);
	}
	clients[*nb_clients] = accept(server_fd, (struct sockaddr*)&sin, &len);
	if (clients[*nb_clients] == -1)
	{
		if (!(this->log((char*)"accept failed", INFO)))
			return (false);
		return (true);
	}
	if (!(this->log((char*)"Accepted new client", INFO)))
		return (false);
	return (true);
	(*nb_clients)++;
}

Tintin_reporter::Tintin_reporter(Tintin_reporter &other)
{
	other._lock_file_fd = _lock_file_fd;
	other._log_file_fd = _log_file_fd;
	other._server_fd = _server_fd;
	other._failed_write = _failed_write;
}

Tintin_reporter::~Tintin_reporter()
{
	flock(_lock_file_fd, LOCK_UN | LOCK_NB);
	close(_lock_file_fd);
	unlink("/var/lock/matt_daemon.lock");
	close(_log_file_fd);
	close(_server_fd);
}

Tintin_reporter    &Tintin_reporter::operator=(Tintin_reporter &other)
{
  return *(new Tintin_reporter(other));
}

bool	Tintin_reporter::try_reopen_log_file(void)
{
	_log_file_fd = open("/var/log/matt_daemon.log", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (_log_file_fd < 0)
		return (false);
	return (true);
}

bool	Tintin_reporter::try_write(char *msg)
{
	int		len;

	len = 0;
	while (msg[len])
		len++;
	if (write(_log_file_fd, msg, len) < 0)
	{
		_failed_write++;
		if (_failed_write < 2 && this->try_reopen_log_file())
			return (this->try_write(msg));
		return (false);
	}
	_failed_write = 0;
	return (true);
}

bool	Tintin_reporter::log(char *msg, log_type type)
{
	time_t		t;
	struct tm	tm;
	char		buf[100];
	char		*type_str;

	t = time(NULL);
	tm = *localtime(&t);
	sprintf(buf, "[%02d/%02d/%d-%02d:%02d:%02d]", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	if (!this->try_write(buf))
		return (false);
	type_str = (char*)"[  LOG  ]";
	if (type == LOG)
		type_str = (char*)"[  LOG  ]";
	else if (type == INFO)
		type_str = (char*)"[ INFO  ]";
	else if (type == ERROR)
		type_str = (char*)"[ ERROR ]";
	if (!this->try_write(type_str))
		return (false);
	if (!this->try_write((char*)" - Matt_daemon: "))
		return (false);
	if (type == LOG && !this->try_write((char*)"User input : " ))
		return (false);
	if (!this->try_write(msg))
		return (false);
	if (!this->try_write((char*)"\n"))
		return (false);
	return (true);
}
