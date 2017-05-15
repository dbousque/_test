

#ifndef LIST_H
# define LIST_H

typedef struct			s_list
{
	void				*elts;
	size_t				size;
	size_t				len;
	size_t				elt_size;
}						t_list;

void					init_list(t_list *list, size_t elt_size);
void					add_to_list(t_list *lst, void *elt);

#endif