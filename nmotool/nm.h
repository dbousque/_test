

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# include "my_malloc.h"

# define BITS_64 1
# define BITS_32 2

typedef struct	s_list
{
	void		**elts;
	int			len;
	int			size;
}				t_list;

size_t			ft_strlen(char *str);
void			ft_putstr(char *str);
void			print_error(char *str);
void			print_format(void);
void			print_error_file(char *str, char *filename);
void			print_hexa_n(size_t numb, int n);
void			print_n_char(char c, int n);
void			*my_mmap(size_t size);

#endif