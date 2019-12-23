/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:02:24 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 23:49:45 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

/*
** Those functions are not used into the program
** They are used to print the different elements that are manipulated during
** execution
** For debuging purpose only
*/

void	ft_print_tab(int *tab_n_ants, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_dprintf(2, " %d |", tab_n_ants[i]);
		i++;
	}
	write(2, "\n", 1);
}

void	ft_print_path(t_list *path)
{
	t_list *head;

	ft_dprintf(2, "len of the path: %d\n", ft_lstlen(path) - 1);
	head = path;
	while (head)
	{
		ft_dprintf(2, "%s - ", ((t_node*)head->content)->name);
		head = head->next;
	}
	write(2, "\n", 1);
}

void	ft_print_combi(t_list *combi)
{
	t_list *head;

	ft_dprintf(2, "combi:\n");
	head = combi;
	while (head)
	{
		ft_print_path(head->content);
		head = head->next;
	}
	write(2, "\n", 1);
}
