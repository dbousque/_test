

#include "myopengl.h"

int		main(void)
{
	t_list	*lst;
	float	f1;
	float	f2;
	float	f3;
	size_t	i;
	float	*elts;

	lst = new_list(sizeof(float));
	f1 = 12.4;
	add_to_list(lst, &f1);
	f1 = 14.5;
	add_to_list(lst, &f1);
	f2 = 42.42;
	add_to_list(lst, &f2);
	i = 0;
	while (i < 40)
	{
		f3 = -12.7;
		add_to_list(lst, &f3);
		i++;
	}
	i = 0;
	elts = (float*)lst->elts;
	while (i < lst->len)
	{
		printf("%f ", elts[i]);
		i++;
	}
	printf("\n");
	return (0);
}