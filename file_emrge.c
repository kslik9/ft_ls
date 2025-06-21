/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_emrge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:13:09 by kslik             #+#    #+#             */
/*   Updated: 2025/06/21 12:15:59 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	split_list(t_file *head, t_file **left, t_file **right)
{
	t_file	*slow;
	t_file	*fast;
	t_file	*prev;

	slow = head;
	fast = head;
	prev = NULL;
	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	prev->next = NULL;
	*left = head;
	*right = slow;
}

static t_file	*merge_sort_files(t_file *head, int flags)
{
	t_file	*left;
	t_file	*right;

	if (!head || !head->next)
		return (head);
	split_list(head, &left, &right);
	left = merge_sort_files(left, flags);
	right = merge_sort_files(right, flags);
	return (merge_files(left, right, flags));
}

t_file	*sort_files(t_file *head, int flags)
{
	return (merge_sort_files(head, flags));
}
