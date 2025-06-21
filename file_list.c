/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:08:42 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:15:09 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	cleanup_file_node(t_file *new_file)
{
	if (new_file->name)
		free(new_file->name);
	if (new_file->path)
		free(new_file->path);
	free(new_file);
}

static t_file	*handle_stat_failure(t_file *new_file, const char *path)
{
	handle_stat_error(path);
	cleanup_file_node(new_file);
	return (NULL);
}

t_file	*create_file_node(const char *name, const char *path)
{
	t_file	*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->name = ft_strdup(name);
	new_file->path = ft_strdup(path);
	new_file->next = NULL;
	if (!new_file->name || !new_file->path)
	{
		cleanup_file_node(new_file);
		return (NULL);
	}
	if (lstat(path, &new_file->stat) == -1)
		return (handle_stat_failure(new_file, path));
	return (new_file);
}

void	add_file_to_list(t_file **head, t_file *new_file)
{
	if (!*head)
	{
		*head = new_file;
		return ;
	}
	new_file->next = *head;
	*head = new_file;
}

void	free_file_list(t_file *head)
{
	t_file	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->path);
		free(temp);
	}
}
