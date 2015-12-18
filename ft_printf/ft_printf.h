

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

int		ft_printf(const char *format, ...);
void	ft_putnbr_un(unsigned int n);
void	ft_putaddr(void *addr);
char	*ft_ntoa_base(long n, char *base);
void	ft_putoctal(long value);

#endif
