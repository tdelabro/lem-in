/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 23:08:25 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 23:06:54 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

/*
** Take a list of t_node*, a specific node
** Return True if the node is in the list
*/

t_list	*ft_node_is_in_lst(t_list *lst, t_node *node)
{
	t_list	*head;

	head = lst;
	while (head)
	{
		if (head->content == node)
			break ;
		head = head->next;
	}
	return (head);
}

/*
** Take a list of list of node and return a list of node containing evey node
** from the input lists.
** Even if  a node is present in different paths, it will only appears once in
** the output.
*/

t_list	*ft_get_used_nodes(t_list *paths)
{
	t_list	*head1;
	t_list	*head2;
	t_list	*used;

	head1 = paths;
	used = NULL;
	while (head1)
	{
		head2 = head1->content;
		while (head2)
		{
			if (!ft_node_is_in_lst(used, head2->content))
				ft_lstappend(&used, \
								ft_lstnew_p(head2->content, sizeof(t_node)));
			head2 = head2->next;
		}
		head1 = head1->next;
	}
	return (used);
}

/*
** Take a list containing t_pipe*, a specific node
** Return True if this specific node is present in the list
*/

t_bool	ft_has_been_visited(t_list *pipes, t_node *node)
{
	t_list	*head;

	head = pipes;
	while (head)
	{
		if (((t_pipe*)head->content)->node == node)
			return (TRUE);
		head = head->next;
	}
	return (FALSE);
}

/*
** Free every links in the list but not it's content.
** Useful when the links has been created by ft_lstnew_p or ft_duplicate_p,
** which is the case for our list of t_node all allong lem-in.
*/

void	ft_free_list_but_content(t_list **lst)
{
	t_list	*head;
	t_list	*prev;

	head = *lst;
	while (head)
	{
		prev = head;
		head = head->next;
		free(prev);
	}
	*lst = NULL;
}

/*
** Free a list of list of nodes, without freeing the nodes themself.
*/

void	ft_free_combi(t_list **combi)
{
	t_list	*head;
	t_list	*tmp;

	head = *combi;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free_list_but_content((t_list**)&tmp->content);
		free(tmp);
	}
	*combi = NULL;
}
