/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_during_bfs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:12:33 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 23:13:21 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_during_bfs.h"

/*
** Input is a list of list of node
** Return True if a node is present in two different list, esle False.
** The starting and ending node are not taken in account.
*/

t_bool	ft_check_overlap(t_list *combi)
{
	t_list	*head_combi;
	t_list	*head_nodes;

	head_combi = combi->next;
	while (head_combi)
	{
		head_nodes = ((t_list*)head_combi->content)->next;
		while (head_nodes->next)
		{
			if (ft_node_is_in_lst(combi->content, head_nodes->content))
				return (TRUE);
			head_nodes = head_nodes->next;
		}
		head_combi = head_combi->next;
	}
	return (FALSE);
}
