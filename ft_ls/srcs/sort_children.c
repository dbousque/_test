/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:01:18 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 17:10:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_strcmp_child_name(void *elt1, void *elt2, void *elt3)
{
	(void)elt3;
	return (-ft_strcmp(((struct dirent*)elt1)->d_name,
											((struct dirent*)elt2)->d_name));
}

int		compare_by_date(void *elt1, void *elt2, void *elt3)
{
	static struct stat		*stat1 = NULL;
	long					date1;

	if (!stat1)
		stat1 = (struct stat*)malloc(sizeof(struct stat));
	if (((struct dirent*)elt1)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	date1 = (long)stat1->st_mtimespec.tv_sec;
	if (((struct dirent*)elt2)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	if (date1 != (long)stat1->st_mtimespec.tv_sec)
		return (date1 - (long)stat1->st_mtimespec.tv_sec);
	return (ft_strcmp_child_name(elt1, elt2, NULL));
}

int		compare_by_access_date(void *elt1, void *elt2, void *elt3)
{
	static struct stat		*stat1 = NULL;
	long					date1;

	if (!stat1)
		stat1 = (struct stat*)malloc(sizeof(struct stat));
	if (((struct dirent*)elt1)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	date1 = (long)stat1->st_atimespec.tv_sec;
	if (((struct dirent*)elt2)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	if (date1 != (long)stat1->st_atimespec.tv_sec)
		return (date1 - (long)stat1->st_atimespec.tv_sec);
	return (ft_strcmp_child_name(elt1, elt2, NULL));
}

int		compare_sizes(void *elt1, void *elt2, void *elt3)
{
	static struct stat		*stat1 = NULL;
	long					size1;

	if (!stat1)
		stat1 = (struct stat*)malloc(sizeof(struct stat));
	if (((struct dirent*)elt1)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	size1 = (long)stat1->st_size;
	if (((struct dirent*)elt2)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	if (size1 != (long)stat1->st_size)
		return (size1 - (long)stat1->st_size);
	return (ft_strcmp_child_name(elt1, elt2, NULL));
}

void	sort_by_name(struct dirent **children, int nb)
{
	if (nb < 400)
		quicksort((void**)children, nb, ft_strcmp_child_name, NULL);
	else
		insertion_sort((void**)children, nb, ft_strcmp_child_name, NULL);
}

void	sort_by_size(struct dirent **children, int nb, char *dir_name)
{
	if (nb < 400)
		quicksort((void**)children, nb, compare_sizes, dir_name);
	else
		insertion_sort((void**)children, nb, compare_sizes, dir_name);
}

void	sort_by_date(struct dirent **children, int nb, char *dir_name, char l)
{
	if (l)
	{
		if (nb < 400)
			quicksort((void**)children, nb, compare_by_date, (void*)dir_name);
		else
			insertion_sort((void**)children, nb,
											compare_by_date, (void*)dir_name);
	}
	else
	{
		if (nb < 400)
			quicksort((void**)children, nb,
									compare_by_access_date, (void*)dir_name);
		else
			insertion_sort((void**)children, nb,
									compare_by_access_date, (void*)dir_name);
	}
}
