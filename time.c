/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:35:01 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:50:45 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_simple_format(t_file *files)
{
	t_file	*current;

	current = files;
	while (current)
	{
		ft_putstr(current->name);
		if (current->next)
		{
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
		}
		current = current->next;
	}
	ft_putchar('\n');
}

char	get_file_type(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

void	set_basic_permissions(mode_t mode, char *perms)
{
	if (mode & S_IRUSR)
		perms[0] = 'r';
	else
		perms[0] = '-';
	if (mode & S_IWUSR)
		perms[1] = 'w';
	else
		perms[1] = '-';
	if (mode & S_IXUSR)
		perms[2] = 'x';
	else
		perms[2] = '-';
	if (mode & S_IRGRP)
		perms[3] = 'r';
	else
		perms[3] = '-';
	if (mode & S_IWGRP)
		perms[4] = 'w';
	else
		perms[4] = '-';
	if (mode & S_IXGRP)
		perms[5] = 'x';
	else
		perms[5] = '-';
}

void	set_other_permissions(mode_t mode, char *perms)
{
	if (mode & S_IROTH)
		perms[6] = 'r';
	else
		perms[6] = '-';
	if (mode & S_IWOTH)
		perms[7] = 'w';
	else
		perms[7] = '-';
	if (mode & S_IXOTH)
		perms[8] = 'x';
	else
		perms[8] = '-';
}

void	set_special_permissions(mode_t mode, char *perms)
{
	if (mode & S_ISUID)
	{
		if (mode & S_IXUSR)
			perms[2] = 's';
		else
			perms[2] = 'S';
	}
	if (mode & S_ISGID)
	{
		if (mode & S_IXGRP)
			perms[5] = 's';
		else
			perms[5] = 'S';
	}
	if (mode & S_ISVTX)
	{
		if (mode & S_IXOTH)
			perms[8] = 't';
		else
			perms[8] = 'T';
	}
}
