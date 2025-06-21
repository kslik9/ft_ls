/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:40:20 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:52:47 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	display_user_group(struct passwd *pwd, struct group *grp)
{
	if (pwd)
		print_padded_string(pwd->pw_name, 8, 1);
	else
		print_padded_string("unknown", 8, 1);
	ft_putchar(' ');
	if (grp)
		print_padded_string(grp->gr_name, 8, 1);
	else
		print_padded_string("unknown", 8, 1);
}

void	display_long_format(t_file *file)
{
	char			perms[11];
	char			*time_str;
	struct passwd	*pwd;
	struct group	*grp;

	perms[0] = get_file_type(file->stat.st_mode);
	get_permissions(file->stat.st_mode, perms + 1);
	perms[10] = '\0';
	pwd = getpwuid(file->stat.st_uid);
	grp = getgrgid(file->stat.st_gid);
	time_str = get_time_string(file->stat.st_mtime);
	ft_putstr(perms);
	ft_putchar(' ');
	ft_putnbr((long)file->stat.st_nlink);
	ft_putchar(' ');
	display_user_group(pwd, grp);
	display_long_format_2(file, time_str);
	free(time_str);
}

void	parse_arguments(int argc, char **argv, t_ls *ls)
{
	int	i;

	i = parse_flags(argc, argv, ls);
	parse_paths(argc, argv, i, ls);
}

void	cleanup_ls(t_ls *ls)
{
	int	i;

	if (ls->paths)
	{
		i = 0;
		while (i < ls->path_count)
		{
			if (ls->paths[i])
				free(ls->paths[i]);
			i++;
		}
		free(ls->paths);
	}
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
