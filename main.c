/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:26:00 by kslik             #+#    #+#             */
/*   Updated: 2025/06/23 09:41:32 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_ls(t_ls *ls)
{
	ls->flags = 0;
	ls->paths = NULL;
	ls->path_count = 0;
}

void	filter_arg(t_ls *ls, char **argv, int i, int j)
{
	if (argv[i][j] == 'l')
		ls->flags |= FLAG_L;
	else if (argv[i][j] == 'R')
		ls->flags |= FLAG_CAP_R;
	else if (argv[i][j] == 'a')
		ls->flags |= FLAG_A;
	else if (argv[i][j] == 'r')
		ls->flags |= FLAG_R;
	else if (argv[i][j] == 't')
		ls->flags |= FLAG_T;
	else
	{
		ft_putstr("ft_ls: invalid option -- '");
		ft_putchar(argv[i][j]);
		ft_putendl("'");
		exit(1);
	}
}

int	parse_flags(int argc, char **argv, t_ls *ls)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		j = 1;
		while (argv[i][j])
		{
			filter_arg(ls, argv, i, j);
			j++;
		}
		i++;
	}
	return (i);
}

void	parse_paths(int argc, char **argv, int start, t_ls *ls)
{
	int	k;

	k = 0;
	ls->path_count = argc - start;
	if (ls->path_count == 0)
	{
		ls->paths = malloc(sizeof(char *));
		ls->paths[0] = ft_strdup(".");
		ls->path_count = 1;
	}
	else
	{
		ls->paths = malloc(sizeof(char *) * ls->path_count);
		while (start < argc)
			ls->paths[k++] = ft_strdup(argv[start++]);
	}
}

int	main(int argc, char **argv)
{
	t_ls	ls;

	init_ls(&ls);
	parse_arguments(argc, argv, &ls);
	ft_ls(&ls);
	cleanup_ls(&ls);
	return (0);
}
