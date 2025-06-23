/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:12:38 by kslik             #+#    #+#             */
/*   Updated: 2025/06/23 09:41:05 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	compare_by_time(t_file *left, t_file *right)
{
	if (left->stat.st_mtime > right->stat.st_mtime)
		return (-1);
	else if (left->stat.st_mtime < right->stat.st_mtime)
		return (1);
	else if (left->stat.st_mtimespec.tv_nsec > right->stat.st_mtimespec.tv_nsec)
		return (-1);
	else if (left->stat.st_mtimespec.tv_nsec < right->stat.st_mtimespec.tv_nsec)
		return (1);
	else
		return (ft_strcmp(left->name, right->name));
}

static int	get_compare_result(t_file *left, t_file *right, int flags)
{
	int	compare;

	if (flags & FLAG_T)
		compare = compare_by_time(left, right);
	else
		compare = ft_strcmp(left->name, right->name);
	if (flags & FLAG_R)
		compare = -compare;
	return (compare);
}

static void	merge_remaining_files(t_file **tail, t_file *left, t_file *right)
{
	if (left)
		*tail = left;
	else
		*tail = right;
}

t_file	*merge_files(t_file *left, t_file *right, int flags)
{
	t_file	*result;
	t_file	**tail;
	int		compare;

	result = NULL;
	tail = &result;
	while (left && right)
	{
		compare = get_compare_result(left, right, flags);
		if (compare <= 0)
		{
			*tail = left;
			left = left->next;
		}
		else
		{
			*tail = right;
			right = right->next;
		}
		tail = &(*tail)->next;
	}
	merge_remaining_files(tail, left, right);
	return (result);
}
