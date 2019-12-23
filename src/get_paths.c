/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:33 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 22:25:19 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_paths.h"

/*
** Those functions go through the list of stored t_pipes, select the links
** contaning the ending node and rewind their parents and the parents of their
** parents untill it reach the starting node, creating in the same time a list
*Â* of paths of same lenghts, from start to end.
*/

static void	ft_rewind(t_list **paths, t_pipe *pipe_end)
{
	t_pipe	*head;

	ft_lstadd(paths, ft_lstnew(NULL, sizeof(t_list)));
	head = pipe_end;
	while (head)
	{
		ft_lstadd((t_list**)&(*paths)->content, \
									ft_lstnew_p(head->node, sizeof(t_node)));
		head = head->parent;
	}
}

t_list		*ft_get_all_equal_paths(t_anthill *anthill, t_list *pipes)
{
	t_list	*paths;
	t_list	*head_pipes;

	paths = NULL;
	head_pipes = pipes;
	while (head_pipes)
	{
		if (((t_pipe*)head_pipes->content)->node == anthill->end)
			ft_rewind(&paths, head_pipes->content);
		head_pipes = head_pipes->next;
	}
	return (paths);
}
