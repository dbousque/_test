

#include "ft_p_server.h"

char	char_in_str(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*find_file_in_dir(char *name, char *dirname)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp_full_path;
	struct stat		file_stat;
	int				fd;

	if (!(dir = opendir(dirname)))
		return (NULL);
	while ((file = readdir(dir)))
	{
		if (ft_strcmp(file->d_name, name) == 0)
		{
			if (!(tmp_full_path = build_file_path(dirname, file->d_name)))
				return (NULL);
			fd = open(tmp_full_path, O_RDONLY);
			if (fd != -1 && fstat(fd, &file_stat) != -1)
			{
				close(fd);
				if (!S_ISDIR(file_stat.st_mode))
				{
					closedir(dir);
					return (tmp_full_path);
				}
			}
			free(tmp_full_path);
		}
	}
	closedir(dir);
	return (NULL);
}

char	*find_file_from_path(char *name, char *path)
{
	int		start;
	int		new_start;
	int		end;
	char	*tmp_file;

	tmp_file = NULL;
	path = ft_strcpy(path);
	start = 0;
	end = 0;
	while (!tmp_file && path[start])
	{
		while (path[end] && path[end] != ':')
			end++;
		if (!path[end])
			new_start = end;
		else
			new_start = end + 1;
		path[end] = '\0';
		tmp_file = find_file_in_dir(name, (void*)path + start);
		start = new_start;
		end = start;
	}
	free(path);
	return (tmp_file);
}

char	*find_executable(char *name, char **env)
{
	int		i;

	if (char_in_str(name, '/'))
		return (ft_strcpy(name));
	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
			return (find_file_from_path(name, (char*)((void*)env[i] + 5)));
		i++;
	}
	return (NULL);
}