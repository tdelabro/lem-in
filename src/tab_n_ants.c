/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_n_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:01:03 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 22:16:03 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Create and initialize the tab.
** Each int is set to the difference between the shortest path and the
** related path.
** Ex. of output: [0, -3, -3, -8, -12, -16, -22]
*/

static void	ft_init_tab_n_ants(t_list *combination, int **tab_n_ants, int len)
{
	t_list	*head;
	t_list	*last;
	int		i;

	if (!(*tab_n_ants = (int*)malloc(sizeof(int) * len)))
		return ;
	last = combination;
	while (last->next)
		last = last->next;
	head = combination;
	i = 0;
	while (head)
	{
		(*tab_n_ants)[i] = ft_lstlen(last->content) - ft_lstlen(head->content);
		head = head->next;
		i++;
	}
}

/*
** Return the sum of the ipositive ints in the tab, ie. the number of ants
** wainting to enter the anthill.
*/

int			ft_sum_tab(int *tab, int len)
{
	int j;
	int sum;

	sum = 0;
	j = 0;
	while (j < len)
	{
		if (tab[j] > 0)
			sum += tab[j];
		j++;
	}
	return (sum);
}

/*
** Fill the initialize tab with ant.
** We go iteratively through the tab, adding one to each int, untill the sum
** of the positive ints in the tab (ie.the number of ants in it), is equal to
** the expected amounth (n_ants).
** Ex. of output: [6, 3, 3, -2, -6, -10, -16] for 12 ants in example tab shown
** before.
*/

void		ft_get_tab_n_ants(t_list *combi, int **tab_n_ants, int n_ants)
{
	int	i;
	int	len;

	len = ft_lstlen(combi);
	ft_init_tab_n_ants(combi, tab_n_ants, len);
	if (!tab_n_ants)
		return ;
	i = len - 1;
	while (ft_sum_tab(*tab_n_ants, len) < n_ants)
	{
		if (i == -1)
			i = len - 1;
		(*tab_n_ants)[i]++;
		i--;
	}
}
