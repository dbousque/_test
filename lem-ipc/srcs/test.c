

#include <stdio.h>

#define dict_init(d) dict_init(&d)

typedef struct	s_dict
{
	int			value;
	void		(*add)(void *value);
	void		(*print)(void);
}				t_dict;

void	dict_init(t_dict *dict)
{
	dict->add = dict_add()
}

int	main(void)
{
	int		val;
	t_dict	dict;

	val = 5;
	dict_init(dict);
	dict.add(val);
	dict_add(dict, val);
	return (0);
}