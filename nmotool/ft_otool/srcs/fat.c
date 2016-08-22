/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 14:32:35 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/19 14:32:37 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void		swap_bytes(char *ptr, size_t size)
{
	char	tmp;
	size_t	i;

	i = 0;
	while (i < size / 2)
	{
		tmp = ptr[i];
		ptr[i] = ptr[size - 1 - i];
		ptr[size - 1 - i] = tmp;
		i++;
	}
}

void		*get_big_endian(char *ptr, size_t size)
{
	char	*res;
	size_t	i;

	res = my_malloc(size);
	i = 0;
	while (i < size)
	{
		res[i] = ptr[size - 1 - i];
		i++;
	}
	return (res);
}

char		tmp_valid(void *start, size_t size)
{
	static void		*st = NULL;
	static size_t	siz = 0;

	if (!start && !size)
	{
		st = NULL;
		siz = 0;
	}
	else if (size)
	{
		st = start;
		siz = size;
	}
	else
	{
		if (start >= st && start < st + siz)
			return (1);
	}
	return (0);
}

uint32_t	look_for_arch(struct fat_arch *arch, uint32_t nb_archs,
								size_t *res_size, cpu_subtype_t cpu_type)
{
	uint32_t			i;
	uint32_t			offset;

	i = 0;
	while (i < nb_archs)
	{
		if (!tmp_valid(((void*)arch) + sizeof(struct fat_arch), 0))
			return (0);
		if (*((cpu_type_t*)get_big_endian((void*)arch, sizeof(cpu_type_t)))
															== cpu_type)
		{
			offset = *((uint32_t*)get_big_endian((void*)arch
			+ sizeof(cpu_type_t) + sizeof(cpu_subtype_t), sizeof(uint32_t)));
			*res_size = *((uint32_t*)get_big_endian((void*)arch
				+ sizeof(cpu_type_t)
				+ sizeof(cpu_subtype_t) + sizeof(uint32_t), sizeof(uint32_t)));
			return (offset);
		}
		i++;
		arch = ((void*)arch) + sizeof(struct fat_arch);
	}
	return (0);
}

void		*get_fat_start(void *ptr, size_t *res_size, size_t size)
{
	struct fat_header	*header;
	uint32_t			nb_archs;
	struct fat_arch		*arch;
	uint32_t			tmp_res;

	tmp_valid(ptr, size);
	header = (struct fat_header*)ptr;
	nb_archs = *((uint32_t*)get_big_endian(((void*)header) + sizeof(uint32_t),
															sizeof(uint32_t)));
	arch = ptr + sizeof(struct fat_header);
	if ((tmp_res = look_for_arch(arch, nb_archs, res_size, CPU_TYPE_X86_64)))
	{
		tmp_valid(NULL, 0);
		return (ptr + tmp_res);
	}
	if ((tmp_res = look_for_arch(arch, nb_archs, res_size, CPU_TYPE_X86)))
	{
		tmp_valid(NULL, 0);
		return (ptr + tmp_res);
	}
	tmp_valid(NULL, 0);
	return (NULL);
}
