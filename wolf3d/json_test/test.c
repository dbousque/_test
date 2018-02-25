

#include "json.h"

int		main(void)
{
	t_value		*json;
	//double		val;

	/*json = read_json("../example_map.json");
	json = get_tab(get_val(json, "blocks"))[1];
	json = get_val(json, "id");
	if (json->type == DOUBLE)
		ft_putendl("DOUBLE\n");
	if (json->type == LONG)
		ft_putendl("LONG\n");
	val = get_double(json);
	if (val == 3)
		ft_putstr("lol\n");
	if (val == 3.0)
		ft_putstr("lol2\n");*/
	json = read_json("../example_map.json");
	if (!json)
		ft_putstr("no json\n");
	else
	{
		print_json(json);
		free_value(json);
	}
	return (0);
}
