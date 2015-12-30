

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
# define ATTR_RESET 0
# define FG_WHITE 37
# define FG_BLACK 30
# define FG_RED 31
# define FG_GREEN 32
# define FG_YELLOW 33
# define FG_BLUE 34
# define FG_MAGENTA 35
# define FG_CYAN 36
# define BG_BLACK 40
# define BG_WHITE 47
# define BG_RED 41
# define BG_GREEN 42
# define BG_YELLOW 43
# define BG_BLUE 44
# define BG_MAGENTA 45
# define BG_CYAN 46

typedef struct			s_format
{
	long long			value;
	unsigned long long	u_value;
	char				specifier;
	char				length;
	char				plus_flag;
	char				sharp_flag;
	char				space_flag;
	char				minus_flag;
	int					precision;
	int					width;
	char				neg_val;
	char				unsigned_val;
	char				has_sign;
	char				char_to_fill;
	char				characters;
}						t_format;

int						ft_printf(const char *format, ...);
int						parse_format(const char *format, t_format *format_var, int *i, va_list ap);
int						ft_putaddr(void *addr, char long_long, char **str, t_format *format);
char					*ft_ntoa_base(long long n, char *base);
char					*ft_ntoa_base_un(unsigned long long n, char *base);
int						ft_putoctal(long long value, char **str);
int						ft_puthexa(unsigned long long value, char **str);
int						ft_putlong_un(unsigned long value, char **str);
int						ft_putlong(long value, char **str);
int						ft_putoctal_un(unsigned long long value, char **str);
int						ft_puthexa_maj(unsigned long long value, char **str);
int						ft_putbinary(long long value, char **str);
int						ft_putunicode(wchar_t *uni, char **str, t_format *format_var);
int						ft_putlonglong_un(unsigned long long value, char **str);
int						ft_putlonglong(long long value, char **str);
int						ft_put_wchar(wchar_t car, char **str);
int						ft_putdouble(double nb, char **str);
void					ft_putstr_unprint(char *inp, char **str);
int						arg_puthexa_maj(va_list ap, char flag, char **str, t_format *format_var);
int						arg_puthexa(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putbinary(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putunicode(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putwchar(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putstr(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putstr_unprint(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putnbr(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putnbr_long(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putnbr_un(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putnbr_un_long(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putchar(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putaddr(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putoctal(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putoctal_long(va_list ap, char flag, char **str, t_format *format_var);
int						arg_putfloat(va_list ap, char flag, char **str, t_format *format_var);
int						get_arg(char **str, va_list ap, t_format *format_var);
char					is_other_maj(char c);
void					get_zero_flag(const char *format, t_format *format_var, int *i);
void					get_minus_flag(const char *format, t_format *format_var, int *i);
void					get_sharp_flag(const char *format, t_format *format_var, int *i);
void					get_space_flag(const char *format, t_format *format_var, int *i);
void					get_plus_flag(const char *format, t_format *format_var, int *i);
void					get_length(const char *format, t_format *format_var, int *i);
void					get_width(const char *format, t_format *format_var, int *i, va_list ap);
void					get_star_width(const char *format, t_format *format_var, int *i, va_list ap);
int						ft_intlen(int nb);
char					is_valid_specifier(char c);
char					ft_isupper(char c);
char					is_other_maj(char c);
void					get_precision(const char *format, t_format *format_var, int *i, va_list ap);
int						bad_specifier(char specifier);
int						invalid_end(char c);
void					ft_change_color_if_asked(const char *format, int *i);
int						print_format(t_format *format, va_list ap);
void					add_prefix_for_addresses_n_sharp(char **value, t_format *format_var, int *length);
void					add_sharp_prefix(char **value, t_format *format_var, int *length);
void					ajust_value_to_width(char **value, t_format *format_var, int *length, int decal);
void					ajust_value_to_width_minus(char **value, t_format *format_var, int *length);
void					append_precision_to_value(char **value, t_format *format_var, int *length, char ori);

#endif
