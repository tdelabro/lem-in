/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes_unavailable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 23:18:19 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 19:09:40 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_pipes_unavailable.h"

/*
** Two complementary function to remove and add pipes between nodes.
*/

/*
** ft_set_pipes_unavailable go through a list of node, and remove from the
** current_node->available_pipes it's connexion to the following node in the
** list.
*/

static void	ft_del_pipe_to_target(t_node *node, t_node *target)
{
	t_list	*head_pipes;
	t_list	*prev;

	head_pipes = node->available_pipes;
	prev = NULL;
	while (head_pipes)
	{
		if (head_pipes->content == target)
		{
			if (!prev)
				node->available_pipes = head_pipes->next;
			else
				prev->next = head_pipes->next;
			free(head_pipes);
			break ;
		}
		prev = head_pipes;
		head_pipes = head_pipes->next;
	}
}

void		ft_set_pipes_unavailable(t_list *path)
{
	t_list	*head_path;

	head_path = path;
	while (head_path->next)
	{
		ft_del_pipe_to_target(head_path->content, head_path->next->content);
		head_path = head_path->next;
	}
}

/*
** ft_restore_pipes go through a list and add to current_node->available_pipes
** a connexion to the next node in the list.
*/

void		ft_restore_pipes(t_list *path)
{
	t_list *head_path;

	head_path = path;
	while (head_path->next)
	{
		ft_lstadd(&((t_node*)head_path->content)->available_pipes, \
				ft_lstnew_p(head_path->next->content, sizeof(t_node)));
		head_path = head_path->next;
	}
}
