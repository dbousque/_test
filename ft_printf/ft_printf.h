

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
int		ft_putnbr_un(unsigned int n);
int		ft_putaddr(void *addr, char long_long);
char	*ft_ntoa_base(long long n, char *base);
char	*ft_ntoa_base_un(unsigned long long n, char *base);
int		ft_putoctal(long long value);
int		ft_puthexa(unsigned long long value);
int		ft_putlong_un(unsigned long value);
int		ft_putlong(long value);
int		ft_putoctal_un(unsigned long long value);
int		ft_putaddr_un(void *addr, char long_long);
int		ft_puthexa_maj(unsigned long long value);
int		ft_putunicode(wchar_t *uni);
int		ft_putlonglong_un(unsigned long long value);
int		ft_putlonglong(long long value);
int		ft_put_wchar(wchar_t car);

#endif
