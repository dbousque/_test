

#include "ft_irc.h"

/*
 * Channels names are strings (beginning with a '&' or '#' character) of
 * length up to 200 characters. Apart from the the requirement that the
 * first character being either '&' or '#'; the only restriction on a
 * channel name is that it may not contain any spaces (' '), a control G
 * (^G or ASCII 7), or a comma (',' which is used as a list item
 * separator by the protocol).
 */

char		valid_channel_name(char *str)
{
	int		i;

	i = 0;
	if (str[0] != '&' && str[0] != '#')
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == 7 || str[i] == ',')
			return (0);
		if (i >= 200)
			return (0);
		i++;
	}
	return (1);
}

/*
 * Each IRC message may consist of up to three main parts: the prefix
 * (optional), the command, and the command parameters (of which there
 * may be up to 15).  The prefix, command, and all parameters are
 * separated by one (or more) ASCII space character(s) (0x20).

 * IRC messages are always lines of characters terminated with a CR-LF
 * (Carriage Return - Line Feed) pair, and these messages shall not
 * exceed 512 characters in length, counting all characters including
 * the trailing CR-LF. Thus, there are 510 characters maximum allowed
 * for the command and its parameters.
 */

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	startswith(char *str, char *start)
{
	int		i;

	i = 0;
	while (start[i] && str[i] == start[i])
		i++;
	if (!start[i])
		return (1);
	return (0);
}

char	contains(char *str, int len, char c)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
 * The protocol messages must be extracted from the contiguous stream of
 * octets. The current solution is to designate two characters, CR and
 * LF, as message separators. Empty  messages  are  silently  ignored,
 * which permits use of the sequence CR-LF between messages
 * without extra problems.
 *
 * The extracted message is parsed into the components <prefix>,
 * <command> and list of parameters matched either by <middle> or
 * <trailing> components.
 *
 * The BNF representation for this is:
 *
 *  <message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
 *  <prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
 *  <command>  ::= <letter> { <letter> } | <number> <number> <number>
 *  <SPACE>    ::= ' ' { ' ' }
 *  <params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
 *  <middle>   ::= <Any *non-empty* sequence of octets not including SPACE
 *                 or NUL or CR or LF, the first of which may not be ':'>
 *  <trailing> ::= <Any, possibly *empty*, sequence of octets not including
 *                   NUL or CR or LF>
 *  <crlf>     ::= CR LF
 */

int		identify_command(char *msg, t_msg *res)
{
	int		i;
	int		end;

	end = -1;
	i = 0;
	while (g_irc_commands[i])
	{
		if (startswith(msg, g_irc_commands[i]))
		{
			end = ft_strlen(g_irc_commands[i]);
			if (msg[end] == ' ' || (msg[end] == '\r' && msg[end + 1] == '\n'))
			{
				res->command = i;
				break ;
			}
			end = -1;
		}
		i++;
	}
	return (end);
}

t_parse_message_res		read_params(char *msg, t_msg *res, int command_end,
																		int i)
{
	int		params_ind;
	char	trailing_param;

	params_ind = -1;
	trailing_param = 0;
	while (msg[i])
	{
		if (msg[i] == '\r')
			break ;
		if (msg[i] == '\n')
			return (FORBIDDEN_CHARACTER);
		if (msg[i] == ' ' && !trailing_param)
		{
			msg[i] = '\0';
			i++;
			while (msg[i] == ' ')
				i++;
			if (msg[i] == ':')
			{
				trailing_param = 1;
				i++;
			}
			params_ind++;
			if (params_ind >= 15)
				return (TOO_MANY_PARAMS);
			res->params[params_ind] = &(msg[i]);
		}
		else
			i++;
	}
	if (msg[i] != '\r' || msg[i + 1] != '\n')
		return (MISSING_CL_LF);
	msg[i] = '\0';
	return (OK);
}

/*
 * Assumes that the string is nul-terminated (512 chars + 1 NUL char)
 */

t_parse_message_res		parse_message(char *msg, int len, t_msg *res)
{
	int		command_end;

	if (len > 512)
		return (TOO_LONG);
	if (contains(msg, len - 1, '\0'))
		return (CONTAINS_NUL);
	if ((command_end = identify_command(msg, res)) == -1)
		return (NO_COMMAND);
	return read_params(msg, res, command_end, command_end);
}

/*
 * 8.13 Channel membership
 *
 * The current server allows any registered local user to join upto 10
 * different channels.  There is no limit imposed on non-local users so
 * that the server remains (reasonably) consistant with all others on a
 * channel membership basis
 */

int		parse_message_error(char *msg, t_parse_message_res res)
{
	if (res == NO_COMMAND)
		printf("Invalid message, doesn't start with a valid command : \"%s\"\n", msg);
	else if (res == TOO_LONG)
		printf("Invalid message, too long (512 characters max)\n");
	else if (res == CONTAINS_NUL)
		printf("Invalid message, contains NUL ('\\0')\n");
	else if (res == FORBIDDEN_CHARACTER)
		printf("Invalid message, contains a forbidden character\n");
	else if (res == TOO_MANY_PARAMS)
		printf("Invalid message, too many parameters (15 max)\n");
	else if (res == MISSING_CL_LF)
		printf("Invalid message, must end with \"\\r\\n\"\n");
	return (0);
}

void	init_msg(t_msg *msg)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		msg->params[i] = NULL;
		i++;
	}
}

void	print_msg(t_msg *msg)
{
	int		i;

	printf("command : %s\n", g_irc_commands[msg->command]);
	if (!msg->params[0])
		printf("no params\n");
	else
		printf("params :\n");
	i = 0;
	while (msg->params[i])
	{
		printf("  - \"%s\"\n", msg->params[i]);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_parse_message_res		res;
	t_msg					parsed_msg;

	init_msg(&parsed_msg);
	res = parse_message(argv[1], ft_strlen(argv[1]), &parsed_msg);
	if (res != OK)
		return parse_message_error(argv[1], res);
	print_msg(&parsed_msg);
	return (0);
}
