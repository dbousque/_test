

#include "irc_client.h"

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

int						identify_command(char *msg, t_msg *res)
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

char					read_params2(char *msg, int *i, char trailing_param)
{
	msg[*i] = '\0';
	(*i)++;
	while (msg[*i] == ' ')
		(*i)++;
	if (msg[*i] == ':')
	{
		trailing_param = 1;
		(*i)++;
	}
	return (trailing_param);
}

t_parse_message_res		read_params(char *msg, t_msg *res, int i)
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
			trailing_param = read_params2(msg, &i, trailing_param);
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
	return (COMMAND_OK);
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
	return read_params(msg, res, command_end);
}

void					init_msg(t_msg *msg)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		msg->params[i] = NULL;
		i++;
	}
}
