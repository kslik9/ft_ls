/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:24:22 by kslik             #+#    #+#             */
/*   Updated: 2025/06/23 10:07:44 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putnbr(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar('0' + (n % 10));
}

void	print_padded_string(const char *str, int width, int left_align)
{
	int	len;
	int	padding;

	len = ft_strlen(str);
	padding = width - len;
	if (!left_align && padding > 0)
	{
		while (padding--)
			ft_putchar(' ');
	}
	ft_putstr(str);
	if (left_align && padding > 0)
	{
		while (padding--)
			ft_putchar(' ');
	}
}

void	display_files(t_file *files, t_ls *ls)
{
	long	total_blocks;
	t_file	*current;

	if (ls->flags & FLAG_L)
	{
		total_blocks = 0;
		current = files;
		while (current)
		{
			total_blocks += current->stat.st_blocks;
			current = current->next;
		}
		ft_putstr("total ");
		ft_putnbr(total_blocks / 2);
		ft_putchar('\n');
		current = files;
		while (current)
		{
			display_long_format(current);
			current = current->next;
		}
	}
	else
		display_simple_format(files);
}

static void	display_symlink(t_file *file, char *link_target)
{
	ssize_t	len;

	if (S_ISLNK(file->stat.st_mode))
	{
		len = readlink(file->path, link_target, 1023);
		if (len != -1)
		{
			link_target[len] = '\0';
			ft_putstr(" -> ");
			ft_putstr(link_target);
		}
	}
}

void	display_long_format_2(t_file *file, char *time_str)
{
	char	link_target[1024];

	ft_putchar(' ');
	ft_putnbr((long)file->stat.st_size);
	ft_putchar(' ');
	ft_putstr(time_str);
	ft_putchar(' ');
	ft_putstr(file->name);
	display_symlink(file, link_target);
	ft_putchar('\n');
}
