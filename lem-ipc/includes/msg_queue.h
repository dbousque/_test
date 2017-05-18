

#ifndef MSG_QUEUE_H
# define MSG_QUEUE_H

# include <stdio.h>
# include <sys/msg.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_MSG_LENGTH 256

typedef struct	s_msq
{
	long		mtype;
	char		mtext[MAX_MSG_LENGTH];
}				t_msg;

int				get_msq_queue(int key, char *error);
char			send_msq_queue(int id, char *data, size_t len, long type);
char			receive_msq_queue(int id, size_t len, long type, char *res);
void			remove_msq_queue(int id);

#endif