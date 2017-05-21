

#include <stdio.h>
#include <stdlib.h>

#define dict_init(d) _dict_init(&d)
#define dict_add(d, s, v) _dict_add(&d, s, &v, sizeof(v))
#define dict_get(d, s) _dict_get(&d, s)

typedef struct	s_dict
{
	void		*value;
	char		name[10];
	char		*long_name;
}				t_dict;

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	_dict_init(t_dict *dict)
{
	dict->value = NULL;
	dict->long_name = NULL;
	dict->name[0] = 'S';
	dict->name[1] = '\0';
}

void	_dict_add(t_dict *dict, char *name, void *value, size_t size)
{
	size_t			i;
	unsigned char	*ori;
	unsigned char	*dest;
	char			long_name;

	long_name = 0;
	i = 0;
	while (name[i])
	{
		dict->name[i] = name[i];
		i++;
		if (i == 10)
		{
			long_name = 1;
			i = ft_strlen(name);
			dict->long_name = (char*)malloc(sizeof(char) * (i + 1));
			i = 0;
			while (name[i])
			{
				dict->long_name[i] = name[i];
				i++;
			}
			dict->long_name[i] = '\0';
			break ;
		}
	}
	if (!long_name)
		dict->name[i] = '\0';
	dict->value = malloc(size);
	ori = (unsigned char*)value;
	dest = (unsigned char*)dict->value;
	i = 0;
	while (i < size)
	{
		dest[i] = ori[i];
		i++;
	}
}

void	*_dict_get(t_dict *dict, char *name)
{
	return (dict->value);
}

int	main(void)
{
	int		val;
	t_dict	dict;

	val = 7;
	dict_init(dict);
	dict_add(dict, "salut", val);
	val = *((int*)dict_get(dict, "salut"));
	printf("val : %d\n", val);
	return (0);
}