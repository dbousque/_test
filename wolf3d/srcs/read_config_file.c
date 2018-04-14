

#include "wolf3d.h"

char	config_err(t_value *config_json, char *msg)
{
	free_value(config_json);
	ft_putstr(msg);
	return (0);
}

char	read_config_file2(t_value *config_json, t_config *config)
{
	t_value		*json;

	if (!(json = get_val(config_json, "width")))
		return (config_err(config_json, "Missing \"width\" field\n"));
	if (json->type != LONG)
		return (config_err(config_json, "\"width\" field is not an int\n"));
	config->width = *((int*)json->data);
	if (config->width < 100 || config->width > 3000)
		return (config_err(config_json, "width isn't >= 100 && <= 3000\n"));
	if (!(json = get_val(config_json, "height")))
		return (config_err(config_json, "Missing \"height\" field\n"));
	if (json->type != LONG)
		return (config_err(config_json, "\"height\" field is not an int\n"));
	config->height = *((int*)json->data);
	if (config->height < 100 || config->height > 3000)
		return (config_err(config_json, "height isn't >= 100 && <= 3000\n"));
	if (!(json = get_val(config_json, "antialiasing")))
		return (config_err(config_json, "Missing \"antialiasing\" field\n"));
	if (json->type != BOOLEAN)
		return (config_err(config_json, "\"antialiasing\" must be boolean\n"));
	config->antialiasing = *((char*)json->data);
	free_value(config_json);
	return (1);
}

char	read_config_file(char *filename, t_config *config)
{
	t_value		*config_json;

	if (!(config_json = read_json(filename, 20 * 1024 * 1024)))
	{
		ft_putstr("Failed to read file \"");
		ft_putstr(filename);
		ft_putstr("\"\n");
		return (0);
	}
	if (config_json->type == 0)
	{
		ft_putstr("Invalid JSON file\n");
		free_value(config_json);
		return (0);
	}
	if (config_json->type != DICT)
		return (config_err(config_json, "File is not a JSON object\n"));
	return (read_config_file2(config_json, config));
}