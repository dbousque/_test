

#include "nm.h"

void	swap_bytes(char *ptr, size_t size)
{
	char	tmp;
	size_t	i;

	while (i < size / 2)
	{
		tmp = ptr[i];
		ptr[i] = ptr[size - 1 - i];
		ptr[size - 1 - i] = tmp;
		i++;
	}
}

void	*get_big_endian(char *ptr, size_t size)
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

void	*get_fat_start(void *ptr, size_t *res_size, size_t size)
{
	struct fat_header	*header;
	uint32_t			nb_archs;
	uint32_t			i;
	struct fat_arch		*arch;
	uint32_t			offset;

	header = (struct fat_header*)ptr;
	nb_archs = *((uint32_t*)get_big_endian(((void*)header) + sizeof(uint32_t),
															sizeof(uint32_t)));
	arch = ptr + sizeof(struct fat_header);
	i = 0;
	while (i < nb_archs)
	{
		if (((void*)arch) + sizeof(struct fat_arch) >= ptr + size)
			return (NULL);
		if (*((cpu_type_t*)get_big_endian((void*)arch, sizeof(cpu_type_t)))
															== CPU_TYPE_X86_64)
		{
			offset = *((uint32_t*)get_big_endian((void*)arch + sizeof(cpu_type_t)
									+ sizeof(cpu_subtype_t), sizeof(uint32_t)));
			*res_size = *((uint32_t*)get_big_endian((void*)arch + sizeof(cpu_type_t)
				+ sizeof(cpu_subtype_t) + sizeof(uint32_t), sizeof(uint32_t)));
			return (ptr + offset);
		}
		i++;
		arch = ((void*)arch) + sizeof(struct fat_arch);
	}
	return (NULL);
}