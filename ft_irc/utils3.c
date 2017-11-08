

#include "ft_irc.h"

void	print_parse_message_error(t_parse_message_res res)
{
	if (res == NO_COMMAND)
		LOG(DEBUG, "Invalid message, doesn't start with a valid command");
	else if (res == TOO_LONG)
		LOG(DEBUG, "Invalid message, too long (512 characters max)");
	else if (res == CONTAINS_NUL)
		LOG(DEBUG, "Invalid message, contains NUL ('\\0')");
	else if (res == FORBIDDEN_CHARACTER)
		LOG(DEBUG, "Invalid message, contains a forbidden character");
	else if (res == TOO_MANY_PARAMS)
		LOG(DEBUG, "Invalid message, too many parameters (15 max)");
	else if (res == MISSING_CL_LF)
		LOG(DEBUG, "Invalid message, must end with \"\\r\\n\"");
}

void	print_msg(t_msg *msg)
{
	int		i;

	LOG(INFO, "command : %s", g_irc_commands[msg->command]);
	if (!msg->params[0])
		LOG(INFO, "  no params");
	else
		LOG(INFO, "params :");
	i = 0;
	while (msg->params[i])
	{
		LOG(INFO, "  - \"%s\"", msg->params[i]);
		i++;
	}
}
