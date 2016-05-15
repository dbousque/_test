

/*t_small_block	**select_small_block(t_malloc_data *data, size_t size)
{
	size_t			i;
	t_small_block	*tmp_block;

	i = 0;
	while (i < data->free_small_blocks->len)
	{
		tmp_block = (t_small_block*)data->free_small_blocks->elts[i];
		if (tmp_block->size >= size)
			return ((t_small_block**)&(data->free_small_blocks->elts[i]));
		i++;
	}
	add_new_small_zone(data);
	return ((t_small_block**)&(data->free_small_blocks->elts[data->free_small_blocks->len - 1]));
}

void	remove_free_block(t_malloc_data *data, t_small_block **free_block)
{
	size_t	i;
	size_t	x;

	char *tmp_str = "removing\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	i = data->free_small_blocks->len - 1;
	while (1)
	{
		if (data->free_small_blocks->elts[i] == *free_block)
		{
			x = i + 1;
			while (x < data->free_small_blocks->len)
			{
				data->free_small_blocks->elts[x - 1] = data->free_small_blocks->elts[x];
				x++;
			}
			data->free_small_blocks->len--;
			return ;
		}
		if (i == 0)
			break ;
		i--;
	}
	tmp_str = "Error, free_block not found\n";
	write(1, tmp_str, ft_strlen(tmp_str));
}

void	reserve_small_block(t_malloc_data *data, t_small_block **free_block,
																size_t size)
{
	t_small_block	*new_free_block;
	char			replace_free_block;

	char *tmp_str = "called\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	replace_free_block = 0;
	if ((*free_block)->size > size + sizeof(t_small_block))
	{
		tmp_str = "in if\n";
		write(1, tmp_str, ft_strlen(tmp_str));
		fflush(stdout);
		new_free_block = (*free_block) + sizeof(t_small_block) + size;
		tmp_str = "after new_free_block\n";
		write(1, tmp_str, ft_strlen(tmp_str));
		fflush(stdout);
		new_free_block->size = (*free_block)->size;
		tmp_str = "after size\n";
		write(1, tmp_str, ft_strlen(tmp_str));
		fflush(stdout);
		new_free_block->free = 1;
		replace_free_block = 1;
	}
	tmp_str = "LAAAAAAA\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	(*free_block)->size = size;
	tmp_str = "MIDDLE\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	(*free_block)->free = 0;
	tmp_str = "BEFORE IF\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	if (replace_free_block)
		*free_block = (*free_block) + sizeof(t_small_block) + size;
	else
	{
		tmp_str = "there\n";
		write(1, tmp_str, ft_strlen(tmp_str));
		fflush(stdout);
		remove_free_block(data, free_block);
	}
}

void	*alloc_new_small_block(t_malloc_data *data, size_t size)
{
	t_small_block	**selected_block;

	char *tmp_str = "before\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	selected_block = select_small_block(data, size);
	tmp_str = "between\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	reserve_small_block(data, selected_block, size);
	tmp_str = "after\n";
	write(1, tmp_str, ft_strlen(tmp_str));
	fflush(stdout);
	return (*selected_block + sizeof(t_small_block));
}*/