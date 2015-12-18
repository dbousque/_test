

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define NO_FLAG 0
# define HH 1
# define H 2
# define L 3
# define LL 4
# define J 5
# define Z 6

int		ft_printf(const char *format, ...);
void	ft_putnbr_un(unsigned int n);
void	ft_putaddr(void *addr);
char	*ft_ntoa_base(long long n, char *base);
char	*ft_ntoa_base_un(unsigned long long n, char *base);
void	ft_putoctal(long value);
void	ft_puthexa(unsigned long value);
void	ft_putlong_un(unsigned long value);
void	ft_putlong(long value);
void	ft_putoctal_un(unsigned long value);
void	ft_putaddr_un(void *addr);
void	ft_puthexa_maj(unsigned long value);

#endif
