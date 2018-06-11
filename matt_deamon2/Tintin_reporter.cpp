

#include "Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter(int log_file_fd) :
	_log_file_fd(log_file_fd),
	_failed_write(0)
{
}

Tintin_reporter::Tintin_reporter(Tintin_reporter &other)
{
	other._log_file_fd = _log_file_fd;
	other._failed_write = _failed_write;
}

Tintin_reporter::~Tintin_reporter()
{
	this->log((char*)"Quitting", INFO);
	close(_log_file_fd);
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
	if (len > 0 && msg[len - 1] == '\n')
		len--;
	if (len <= 0)
		return (true);
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
	sprintf(buf, "[%02d/%02d/%d-%02d:%02d:%02d] ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
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
