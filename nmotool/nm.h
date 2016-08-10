

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

size_t		ft_strlen(char *str);
void		ft_putstr(char *str);
void		print_error(char *str);
void		print_format(void);
void		print_error_file(char *str, char *filename);

#endif