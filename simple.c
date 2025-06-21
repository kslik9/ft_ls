/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:35:31 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:48:17 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*format_recent_time(char *time_str)
{
	char	*result;

	result = malloc(13);
	if (!result)
		return (ft_strdup("unknown"));
	strncpy(result, time_str + 4, 12);
	result[12] = '\0';
	return (result);
}

static char	*format_old_time(char *time_str)
{
	char	*result;

	result = malloc(13);
	if (!result)
		return (ft_strdup("unknown"));
	strncpy(result, time_str + 4, 7);
	strncpy(result + 7, time_str + 19, 5);
	result[12] = '\0';
	return (result);
}

char	*get_time_string(time_t file_time)
{
	char		*time_str;
	time_t		current_time;
	double		diff;

	time_str = ctime(&file_time);
	if (!time_str)
		return (ft_strdup("unknown"));
	current_time = time(NULL);
	diff = difftime(current_time, file_time);
	if (diff < 6 * 30 * 24 * 3600)
		return (format_recent_time(time_str));
	else
		return (format_old_time(time_str));
}

void	get_permissions(mode_t mode, char *perms)
{
	set_basic_permissions(mode, perms);
	set_other_permissions(mode, perms);
	set_special_permissions(mode, perms);
}
