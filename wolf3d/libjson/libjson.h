#ifndef LIBJSON_H
# define LIBJSON_H

# include <fcntl.h>
# include "libdodo.h"

# define LONG 1
# define DOUBLE 2
# define STRING 3
# define DICT 4
# define ARRAY 5
# define BOOLEAN 6
# define DELETED_VALUE -1

typedef struct	s_value
{
	char		type;
	void		*data;
}				t_value;

typedef struct	s_dict
{
	char		**keys;
	t_value		**values;
}				t_dict;

t_value			*read_json(char *filename, int max_size);
void			print_json(t_value *json);
void			print_elt(t_value *elt, int nb_tabs, char print_tabs);
void			free_value(t_value *value);
t_value			*handle_buf(char *buf, int *i);
double			get_double(t_value *value);
long			get_long(t_value *value);
char			*get_string(t_value *value);
char 			get_bool(t_value *value);
t_value			*get_val(t_value *dict_inp, char *key);
t_value			*get(t_value *array, int i);
t_value			**get_tab(t_value *value);
t_dict			*get_dict(t_value *dict_val);
t_value			*read_json_str(char *content);

/* internal */

void			*open_failed(void);
void			*max_size_exceeded(char *filename, int max_size);
void			malloc_error(void);
void			wrong_format(void);
void			no_colon(void);
void			value_type_error(void);
t_value			*handle_array(char *buf, int *i);
t_value			*handle_dict(char *buf, int *i);
t_value			*keys_n_values_to_value(t_list *keys, t_list *values);
t_value			*string_value(char *buf, int *i);
t_value			*void_value(void);
void			go_to_next_char(char *buf, int *i, char c);
char			*take_up_to_char(char *buf, int *i, char c, char preceed, int *len);
t_list			*new_list_elt(void *content, int content_size);
void			go_to_next_char_not_in_string(char *buf, int *i, char c);

#endif
