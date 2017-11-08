

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
