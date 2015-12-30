/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:27:32 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:35:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "format_var.h"
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

typedef unsigned char	t_uchar;

int		ft_printf(const char *format, ...);
int		parse_format(const char *format, t_format *formatv, int *i, va_list ap);
int		ft_putaddr(void *addr, char long_long, char **str, t_format *format);
char	*ft_ntoa_base(long long n, char *base);
char	*ft_ntoa_base_un(unsigned long long n, char *base);
int		ft_putoctal(long long value, char **str);
int		ft_puthexa(unsigned long long value, char **str);
int		ft_putlong_un(unsigned long value, char **str);
int		ft_putlong(long value, char **str);
int		ft_putoctal_un(unsigned long long value, char **str);
int		ft_puthexa_maj(unsigned long long value, char **str);
int		ft_putbinary(long long value, char **str);
int		ft_putunicode(wchar_t *uni, char **str, t_format *format_var);
int		ft_putlonglong_un(unsigned long long value, char **str);
int		ft_putlonglong(long long value, char **str);
int		ft_put_wchar(wchar_t car, char **str);
int		ft_putdouble(double nb, char **str);
int		ft_put_wchar(wchar_t car, char **str);
void	ft_putstr_unprint(char *inp, char **str);
int		arg_puthexa_maj(va_list ap, char flag, char **str, t_format *format);
int		arg_puthexa(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putbinary(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putunicode(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putwchar(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putstr(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putstr_unprint(va_list ap, char flag, char **str, t_format *format);
int		arg_putnbr(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putnbr_long(va_list ap, char flag, char **str, t_format *format);
int		arg_putnbr_un(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putnbr_un_long(va_list ap, char flag, char **str, t_format *format);
int		arg_putchar(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putaddr(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putoctal(va_list ap, char flag, char **str, t_format *format_var);
int		arg_putoctal_long(va_list ap, char flag, char **str, t_format *format);
int		arg_putfloat(va_list ap, char flag, char **str, t_format *format_var);
int		get_arg(char **str, va_list ap, t_format *format_var);
char	is_other_maj(char c);
void	get_zero_flag(const char *format, t_format *format_var, int *i);
void	get_minus_flag(const char *format, t_format *format_var, int *i);
void	get_sharp_flag(const char *format, t_format *format_var, int *i);
void	get_space_flag(const char *format, t_format *format_var, int *i);
void	get_plus_flag(const char *format, t_format *format_var, int *i);
void	get_length(const char *format, t_format *format_var, int *i);
void	get_width(const char *format, t_format *format_var, int *i, va_list ap);
void	get_star_width(const char *f, t_format *fo, int *i, va_list ap);
int		ft_intlen(int nb);
char	is_valid_specifier(char c);
char	ft_isupper(char c);
char	is_other_maj(char c);
void	get_precision(const char *f, t_format *fo, int *i, va_list ap);
int		bad_specifier(char specifier);
int		invalid_end(char c);
void	ft_change_color_if_asked(const char *format, int *i);
int		print_format(t_format *format, va_list ap);
void	add_prefix_for_addr_n_sharp(char **val, t_format *forma, int *len);
void	add_sharp_prefix(char **value, t_format *format_var, int *length);
void	ajust_value_to_width(char **val, t_format *format, int *len, int decal);
void	ajust_value_to_width_minus(char **val, t_format *format_var, int *len);
void	append_precision_to_value(char **val, t_format *f, int *len, char ori);
int		ft_put_one_uni(wchar_t car, char *str);
int		ft_put_two_uni(wchar_t car, char *str);
int		ft_put_three_uni(wchar_t car, char *str);
int		ft_put_four_uni(wchar_t car, char *str);
void	cpy_n_bits(char *res, char *tmp, int nb);
t_uchar	byte_array_to_uchar(char *byte);
void	write_res_to_tmp(char *res, char *tmp, int tmp_length);
void	apply_precision(char **value, t_format *fo, int *length);
void	cut_digits(char **value, t_format *format, int *length);
char	is_spec_numb(char c);
void	void_str(char **value, int *length);

#endif
