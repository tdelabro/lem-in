/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_paths_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:20:37 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 22:25:53 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "combine_paths_utilities.h"

void		ft_eliminate_passing(t_bool **tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (tab[i][j] == TRUE && tab[j][i] == TRUE)
			{
				tab[i][j] = FALSE;
				tab[j][i] = FALSE;
			}
			j++;
		}
		i++;
	}
}

static void	ft_swap_paths(t_list **paths, t_list **head, t_list **prev, \
		t_bool *sorted)
{
	if (ft_lstlen((*head)->next->content) > ft_lstlen((*head)->content))
	{
		*sorted = FALSE;
		if (*prev == NULL)
		{
			*paths = (*head)->next;
			(*head)->next = (*head)->next->next;
			(*paths)->next = *head;
			*head = (*paths)->next;
			*prev = *paths;
		}
		else
		{
			(*prev)->next = (*head)->next;
			(*head)->next = (*head)->next->next;
			(*prev)->next->next = *head;
			*head = (*prev)->next;
		}
	}
	else
	{
		*prev = *head;
		*head = (*head)->next;
	}
}

void		ft_sort_paths_by_length(t_list **paths)
{
	t_list	*head;
	t_list	*prev;
	t_bool	sorted;

	sorted = FALSE;
	while (sorted == FALSE)
	{
		sorted = TRUE;
		head = *paths;
		prev = NULL;
		while (head->next)
			ft_swap_paths(paths, &head, &prev, &sorted);
	}
}

static void	ft_fill_new_path(t_bool **tab, t_list *paths, t_list *used, \
											int *tab_i_len)
{
	int	j;

	j = 0;
	while (j < tab_i_len[1])
	{
		if (tab[tab_i_len[0]][j] == TRUE)
		{
			ft_lstappend((t_list**)&paths->content, \
					ft_lstnew_p(ft_get_node(used, j), sizeof(t_node)));
			tab[tab_i_len[0]][j] = FALSE;
			tab_i_len[0] = j;
			j = -1;
		}
		j++;
	}
}

t_list		*ft_get_new_paths(t_bool **tab, t_list *used)
{
	int		tab_i_len[2];
	t_list	*paths;
	t_list	*tmp;

	paths = NULL;
	tab_i_len[1] = ft_lstlen(used);
	while (1)
	{
		tab_i_len[0] = 0;
		ft_lstadd(&paths, ft_lstnew_p(ft_lstnew_p(ft_get_node(used, 0), \
						sizeof(t_node)), sizeof(t_list)));
		ft_fill_new_path(tab, paths, used, tab_i_len);
		if (tab_i_len[0] == 0)
			break ;
	}
	tmp = paths;
	paths = paths->next;
	free(tmp->content);
	free(tmp);
	return (paths);
}
