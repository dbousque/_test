

#include "nm.h"

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

char	match_sect_name_with_type(char *seg_name, char *sect_name)
{
	if (ft_streq(seg_name, SEG_TEXT) && ft_streq(sect_name, SECT_TEXT))
		return ('T');
	if (ft_streq(seg_name, SEG_DATA) && ft_streq(sect_name, SECT_DATA))
		return ('D');
	if (ft_streq(seg_name, SEG_DATA) && ft_streq(sect_name, SECT_BSS))
		return ('B');
	//if (ft_streq(seg_name, SEG_DATA) && ft_streq(sect_name, SECT_COMMON))
	//	return ('C');
	return ('S');
}

void	print_local_or_ext_64(struct nlist_64 *symbol, char c)
{
	char	to_print;

	to_print = c;
	if (c >= 'A' && c <= 'Z' && !(symbol->n_type & N_EXT))
		to_print = c - 'A' + 'a';
	write(1, &to_print, 1);
}

void	print_local_or_ext_32(struct nlist *symbol, char c)
{
	char	to_print;

	to_print = c;
	if (c >= 'A' && c <= 'Z' && !(symbol->n_type & N_EXT))
		to_print = c - 'A' + 'a';
	write(1, &to_print, 1);
}