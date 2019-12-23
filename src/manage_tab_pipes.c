/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_tab_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:37:57 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 22:16:36 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manage_tab_pipes.h"

/*
** All the finction in this file are used to manipulate the tab needed to 
** handle overlaping paths
** See combine_paths.c
*/

/*
** Scan the list of node to return the index in the tab associated with a
** particular node
*/

int		ft_get_index(t_list *used, t_node *node)
{
	t_list	*head;
	int		i;

	i = 0;
	head = used;
	while (head)
	{
		if (head->content == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/*
** Scan the list of node to return the node associated with a particular index
** in the tab
*/

t_node	*ft_get_node(t_list *used, int index)
{
	t_list	*head;
	int		i;

	i = 0;
	head = used;
	while (head)
	{
		if (i == index)
			return (head->content);
		head = head->next;
		i++;
	}
	return (NULL);
}

/*
** Malloc and store the tab. Set every bit in it to 0.
*/

t_bool	**ft_init_tab(int size)
{
	int		i;
	t_bool	**tab;

	tab = ft_memalloc(sizeof(t_bool*) * size);
	i = 0;
	while (i < size)
	{
		if (!(tab[i] = ft_memalloc(sizeof(t_bool) * size)))
		{
			while (--i >= 0)
			{
				ft_memdel((void**)&tab[i]);
				ft_memdel((void**)&tab);
				return (NULL);
			}
		}
		i++;
	}
	return (tab);
}

/*
** Free the whole tab and it's content.
*/

void	ft_del_tab(t_bool **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void**)&tab[i]);
		i++;
	}
	ft_memdel((void**)&tab);
}
