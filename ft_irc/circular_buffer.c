

#include "ft_irc.h"

void	init_circular_buffer(t_circular_buffer *b)
{
	b->start = 0;
	b->end = 0;
}

void	circular_buffer_write(t_circular_buffer *b, char *data, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		b->data[b->end] = data[i];
		b->end++;
		if (b->end == USER_BUFFER_SIZE)
			b->end = 0;
		if (b->end == b->start)
		{
			b->start++;
			if (b->start == USER_BUFFER_SIZE)
				b->start = 0;
		}
		i++;
	}
}

int		circular_buffer_read(t_circular_buffer *b, char *dest)
{
	int		i;

	i = 0;
	while (b->start != b->end)
	{
		dest[i] = b->data[b->start];
		b->start++;
		if (b->start == USER_BUFFER_SIZE)
			b->start = 0;
		i++;
	}
	b->start = 0;
	b->end = 0;
	return (i);
}

int		circular_buffer_cpy(t_circular_buffer *b, char *dest)
{
	int		i;
	int		ori_start;
	int		ori_end;

	ori_start = b->start;
	ori_end = b->end;
	i = circular_buffer_read(b, dest);
	b->start = ori_start;
	b->end = ori_end;
	return (i);
}

char	empty(t_circular_buffer *b)
{
	if (b->start == b->end)
		return (1);
	return (0);
}
