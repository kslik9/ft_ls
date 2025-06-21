/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:51:59 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:54:01 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstr(const char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putendl(const char *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}

void	print_error(const char *path, const char *message)
{
	ft_putstr("ft_ls: ");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putendl(message);
}

void	handle_stat_error(const char *path)
{
	ft_putstr("ft_ls: cannot access '");
	ft_putstr(path);
	ft_putstr("': ");
	ft_putendl(strerror(errno));
}
