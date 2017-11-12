

#include "ft_irc.h"

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

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

	LOG(INFO, "Command : %s", g_irc_commands[msg->command]);
	if (!msg->params[0])
		LOG(INFO, "No params");
	else
		LOG(INFO, "Params :");
	i = 0;
	while (msg->params[i])
	{
		LOG(INFO, "  - \"%s\"", msg->params[i]);
		i++;
	}
}

void	log_user(t_user *user, char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	log_start(INFO);
	printf("<- ('%s') %s", user->nickname, str);
	log_end(INFO);
	circular_buffer_write(&(user->write_buffer), str, i);
}

void	wrong_nb_params(t_user *user, char *command_name, int nb_params,
																int expected)
{
	char	str[200];

	snprintf(str, 200, "Command '%s' expects %d parameter%s, but got %d",
				command_name, expected, expected > 1 ? "s" : "", nb_params);
	log_user(user, str);
}
