/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:24:06 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:33:18 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*create_full_path(const char *path, const char *name)
{
	char	*full_path;
	size_t	path_len;

	path_len = ft_strlen(path);
	full_path = malloc(path_len + ft_strlen(name) + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, path);
	if (path_len > 0 && path[path_len - 1] != '/')
	{
		full_path[path_len] = '/';
		full_path[path_len + 1] = '\0';
		ft_strcat(full_path, name);
	}
	else
	{
		ft_strcat(full_path, name);
	}
	return (full_path);
}

static void	process_directory_entry(struct dirent *entry, const char *path,
		t_file **files, t_ls *ls)
{
	char	*full_path;
	t_file	*new_file;

	if (!(ls->flags & FLAG_A) && entry->d_name[0] == '.')
		return ;
	full_path = create_full_path(path, entry->d_name);
	if (!full_path)
		return ;
	new_file = create_file_node(entry->d_name, full_path);
	free(full_path);
	if (new_file)
		add_file_to_list(files, new_file);
}

void	read_directory_entries(DIR *dir, const char *path,
		t_file **files, t_ls *ls)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry != NULL)
	{
		process_directory_entry(entry, path, files, ls);
		entry = readdir(dir);
	}
}

static int	should_recurse_into_dir(t_file *current)
{
	if (!S_ISDIR(current->stat.st_mode))
		return (0);
	if (ft_strcmp(current->name, ".") == 0)
		return (0);
	if (ft_strcmp(current->name, "..") == 0)
		return (0);
	return (1);
}

void	handle_recursive_directories(t_file *files, t_ls *ls)
{
	t_file	*current;

	if (!(ls->flags & FLAG_R))
		return ;
	current = files;
	while (current)
	{
		if (should_recurse_into_dir(current))
		{
			ft_putchar('\n');
			ft_putstr(current->path);
			ft_putendl(":");
			process_directory(current->path, ls, 1);
		}
		current = current->next;
	}
}
