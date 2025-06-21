/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:18:51 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:25:36 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_directory_header(const char *path, int i, int path_count)
{
	if (path_count > 1)
	{
		if (i > 0)
			ft_putchar('\n');
		ft_putstr(path);
		ft_putendl(":");
	}
}

static void	process_single_path(t_ls *ls, int i)
{
	struct stat	st;

	if (stat(ls->paths[i], &st) == -1)
	{
		handle_stat_error(ls->paths[i]);
		return ;
	}
	if (S_ISDIR(st.st_mode))
	{
		print_directory_header(ls->paths[i], i, ls->path_count);
		process_directory(ls->paths[i], ls, 0);
	}
	else
	{
		process_file(ls->paths[i], ls);
	}
}

void	ft_ls(t_ls *ls)
{
	int	i;

	i = 0;
	while (i < ls->path_count)
	{
		process_single_path(ls, i);
		i++;
	}
}

void	process_directory(const char *path, t_ls *ls, int is_recursive)
{
	DIR		*dir;
	t_file	*files;

	files = NULL;
	dir = opendir(path);
	if (!dir)
	{
		print_error(path, "cannot open directory");
		return ;
	}
	read_directory_entries(dir, path, &files, ls);
	closedir(dir);
	if (files)
	{
		files = sort_files(files, ls->flags);
		display_files(files, ls, path);
		handle_recursive_directories(files, ls);
		free_file_list(files);
	}
}

void	process_file(const char *path, t_ls *ls)
{
	t_file	*file;

	file = create_file_node(path, path);
	if (file)
	{
		display_files(file, ls, NULL);
		free_file_list(file);
	}
}
