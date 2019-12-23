/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:33 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 23:10:59 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs.h"

static t_node	*ft_get_exact_node(t_list *used_paths, t_node *current_node)
{
	t_list	*head_paths;
	t_list	*head_nodes;
	t_list	*prev;

	head_paths = used_paths;
	while (head_paths)
	{
		prev = NULL;
		head_nodes = head_paths->content;
		while (head_nodes->next)
		{
			if (head_nodes->content == current_node)
				return (prev->content);
			prev = head_nodes;
			head_nodes = head_nodes->next;
		}
		head_paths = head_paths->next;
	}
	return (NULL);
}

static t_pipe	*ft_generate_pipe(t_node *node, t_pipe *parent)
{
	t_pipe *new;

	if (!(new = (t_pipe*)malloc(sizeof(t_pipe))))
		return (NULL);
	new->node = node;
	new->parent = parent;
	return (new);
}

/*
** We will refuse the new node as a valid continuation if :
** - the current node is the start of the anthill
**   and the candidate has already been used in an other path
** - the current node is has already been used in an other path,
**   the previous one hasn't,
**   and the candidate is not the exact pevious one on the used path
** - the current and previous nodes one are both already used in an other path
**   and the candidate is already used but is not the exact previous one needed
*/

static void		ft_process_new_pipes(t_anthill *anthill, t_list *tab_lists[4], \
													t_pipe *pipe, t_node *node)
{
	t_list *used_nodes;

	used_nodes = ft_get_used_nodes(tab_lists[3]);
	if ((anthill->start == pipe->node && !ft_node_is_in_lst(used_nodes, node)) \
		|| (anthill->start != pipe->node \
		&& ((!ft_node_is_in_lst(used_nodes, pipe->node)\
		|| (ft_node_is_in_lst(used_nodes, pipe->node)\
		&& ((!ft_node_is_in_lst(used_nodes, pipe->parent->node)\
		&& ft_get_exact_node(tab_lists[3], pipe->node) == node)\
		|| (ft_node_is_in_lst(used_nodes, pipe->parent->node) \
		&& !(ft_node_is_in_lst(used_nodes, node) \
		&& ft_get_exact_node(tab_lists[3], pipe->node) != node))))))))
	{
		ft_lstappend(&tab_lists[0], \
				ft_lstnew_p(ft_generate_pipe(node, pipe), sizeof(t_pipe)));
		ft_lstappend(&tab_lists[2], ft_lstnew_p(node, sizeof(t_node)));
	}
	ft_free_list_but_content(&used_nodes);
}

/*
** Procces to editing joining queue and new queue when we go one step further
** to the start
**
** Distance:	1		2	...		n
**
**				A ---	C	...	
**			/	  \
** Starting ---	B ---	D	...		Ending
**				|
**				 \___	E	...
**
** Scan the available_pipe of the node currently in queue. If one of them is
** still new, we add send it to process_new_pipe and if it fulfil the conditions
** we add it to the queue and store a dedicated t_pipe.
*/

static void		ft_take_action(t_anthill *anthill, t_list *head_queue, \
															t_list *tab[4])
{
	t_list	*head_pipes;

	if (tab[2] && ((t_pipe*)head_queue->content)->node == tab[2]->content)
	{
		ft_lstjoin(&tab[1], tab[2]);
		tab[2] = NULL;
	}
	head_pipes = ((t_pipe*)head_queue->content)->node->available_pipes;
	while (head_pipes)
	{
		if (!ft_node_is_in_lst(tab[1], head_pipes->content))
			ft_process_new_pipes(anthill, tab, \
								head_queue->content, head_pipes->content);
		head_pipes = head_pipes->next;
	}
}

/*
** tab = [*queue, *visited, *tmp_visited, *used_paths]
**
** A classic breadth first algorithm that generate a list of t_pipe strucs
** that keep in memory the parent node of each ne node.
** If two node equaly distant from start are both connected to a new unvisited
** node, we create two tÂ_pipe for this node, each linked to a diferent parent.
** 
** Once the ending node has been reached, ft_get_all_equal_paths allow us to
** travell back to the starting node, creating a list of all the found path of
** equal length.
*/

t_list			*ft_bfs(t_anthill *anthill, t_list *used_paths)
{
	t_list	*tab[4];
	t_list	*head_queue;

	tab[0] = NULL;
	tab[1] = NULL;
	tab[2] = NULL;
	tab[3] = used_paths;
	ft_lstadd(&tab[0],\
		ft_lstnew_p(ft_generate_pipe(anthill->start, NULL), sizeof(t_pipe)));
	ft_lstadd(&tab[1], ft_lstnew_p(anthill->start, sizeof(t_node)));
	head_queue = tab[0];
	while (head_queue && !ft_has_been_visited(head_queue, anthill->end))
	{
		ft_take_action(anthill, head_queue, tab);
		head_queue = head_queue->next;
	}
	ft_free_list_but_content(&tab[1]);
	ft_free_list_but_content(&tab[2]);
	head_queue = ft_get_all_equal_paths(anthill, tab[0]);
	ft_lstclear(&tab[0]);
	return (head_queue);
}
