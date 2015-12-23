

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

typedef struct		s_format
{
	char			specifier;
	char			length;
	char			plus_flag;
	char			sharp_flag;
	char			space_flag;
	char			minus_flag;
	int				precision;
	int				width;
	char			neg_val;
	char			unsigned_val;
	char			has_sign;
	char			char_to_fill;
	char			characters;
}					t_format;

int					ft_printf(const char *format, ...);
int					ft_putaddr(void *addr, char long_long, char **str);
char				*ft_ntoa_base(long long n, char *base);
char				*ft_ntoa_base_un(unsigned long long n, char *base);
int					ft_putoctal(long long value, char **str);
int					ft_puthexa(unsigned long long value, char **str);
int					ft_putlong_un(unsigned long value, char **str);
int					ft_putlong(long value, char **str);
int					ft_putoctal_un(unsigned long long value, char **str);
int					ft_putaddr_un(void *addr, char long_long, char **str);
int					ft_puthexa_maj(unsigned long long value, char **str);
int					ft_putunicode(wchar_t *uni, char **str);
int					ft_putlonglong_un(unsigned long long value, char **str);
int					ft_putlonglong(long long value, char **str);
int					ft_put_wchar(wchar_t car, char **str);
int					arg_puthexa_maj(va_list ap, char flag, char **str, t_format *format_var);
int					arg_puthexa(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putunicode(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putwchar(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putstr(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putnbr(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putnbr_long(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putnbr_un(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putnbr_un_long(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putchar(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putaddr(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putoctal(va_list ap, char flag, char **str, t_format *format_var);
int					arg_putoctal_long(va_list ap, char flag, char **str, t_format *format_var);
int					get_arg(char **str, va_list ap, t_format *format_var);

#endif
