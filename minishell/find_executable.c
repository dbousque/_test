

#include "minishell.h"

void	print_list(t_linked_list *list)
{
	int		i;

	i = 0;
	while (i < list->len)
	{
		ft_putstr(list->elts[i]);
		ft_putstr("\n");
		i++;
	}
}

void	get_files_in_dir(char *path, t_linked_list *files, char dirs, char not_exec)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp_full_path;
	struct stat		file_stat;

	if (!(dir = opendir(path)))
		return ;
	while ((file = readdir(dir)))
	{
		tmp_full_path = build_file_path(path, file->d_name);
		if (stat(tmp_full_path, &file_stat) != -1)
		{
			if (dirs || !S_ISDIR(file_stat.st_mode))
			{
				if (not_exec || (access(tmp_full_path, X_OK) != -1 && dirs != 2))
					add_to_list(files, ft_strdup(file->d_name));
			}
		}
		free(tmp_full_path);
	}
	closedir(dir);
}

char	*get_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

t_linked_list	*get_files_from_path(char **env)
{
	t_linked_list	*dirs;
	t_dir			*tmp_dir;
	char			**paths;
	char			*path;
	size_t			i;

	path = get_path(env);
	if (!path)
		return (NULL);
	paths = ft_strsplit(path, ':');
	dirs = new_list();
	i = 0;
	while (paths[i])
	{
		if (!(tmp_dir = (t_dir*)malloc(sizeof(t_dir))))
			malloc_error();
		tmp_dir->files = new_list();
		tmp_dir->path = ft_strdup(paths[i]);
		get_files_in_dir(paths[i], tmp_dir->files, 0, 0);
		add_to_list(dirs, tmp_dir);
		i++;
	}
	free_ptrptr((void**)paths);
	return (dirs);
}

void	get_files_from_path2(char **env, t_linked_list *files)
{
	char			**paths;
	char			*path;
	size_t			i;

	path = get_path(env);
	if (!path)
		return ;
	paths = ft_strsplit(path, ':');
	i = 0;
	while (paths[i])
	{
		get_files_in_dir(paths[i], files, 0, 0);
		i++;
	}
	free_ptrptr((void**)paths);
}

char	*build_file_path(char *dir_path, char *file_name)
{
	size_t	i;
	size_t	name_len;
	char	*res;
	char	add_slash;

	name_len = ft_strlen(file_name);
	add_slash = 1;
	i = 0;
	while (dir_path[i])
		i++;
	if (i == 0 || dir_path[i - 1] == '/')
		add_slash = 0;
	if (!(res = (char*)malloc(sizeof(char) * (i + add_slash + name_len + 1))))
		malloc_error();
	res[i + add_slash + name_len] = '\0';
	i = 0;
	while (dir_path[i])
	{
		res[i] = dir_path[i];
		i++;
	}
	name_len = i + add_slash;
	if (add_slash)
		res[i] = '/';
	i = 0;
	while (file_name[i])
	{
		res[name_len + i] = file_name[i];
		i++;
	}
	return (res);
}

char	file_in_list(char *file, t_linked_list *files)
{
	int		i;

	i = 0;
	while (i < files->len)
	{
		if (ft_strcmp(file, files->elts[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*find_exec_from_path(char *prog, t_linked_list *dirs)
{
	int		i;

	i = 0;
	while (i < dirs->len)
	{
		if (file_in_list(prog, ((t_dir*)dirs->elts[i])->files))
			return (build_file_path(((t_dir*)dirs->elts[i])->path, prog));
		i++;
	}
	return (NULL);
}

char	*find_exec_current_dir(char *prog)
{
	return (prog);
}

void	command_not_found(char *command)
{
	ft_putstr(command);
	ft_putstr(": command not found\n");
}

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

char	*no_such_file_or_dir(char *prog)
{
	ft_putstr("minishell: ");
	ft_putstr(prog);
	ft_putstr(": No such file or directory\n");
	return (NULL);
}

char	*is_a_dir(char *prog)
{
	ft_putstr("minishell: ");
	ft_putstr(prog);
	ft_putstr(": Is a directory\n");
	return (NULL);
}

char	*permission_denied(char *prog)
{
	ft_putstr("minishell: ");
	ft_putstr(prog);
	ft_putstr(": Permission denied\n");
	return (NULL);
}

char	*find_exec_with_path(char *prog)
{
	struct stat	file;

	if (stat(prog, &file) == -1)
		return (no_such_file_or_dir(prog));
	if (S_ISDIR(file.st_mode))
		return (is_a_dir(prog));
	if (access(prog, X_OK) == -1)
		return (permission_denied(prog));
	return (prog);
}

char	*find_executable(char *prog, char **env)
{
	t_linked_list	*files;
	char			*exec;

	exec = NULL;
	if (char_in_str(prog, '/'))
		exec = find_exec_with_path(prog);
	else
	{
		files = get_files_from_path(env);
		if (files)
			exec = find_exec_from_path(prog, files);
		if (!exec)
		{
			// bonus : add recommendation for the right command (mistyping)
			command_not_found(prog);
			return (NULL);
		}
	}
	return (exec);
}