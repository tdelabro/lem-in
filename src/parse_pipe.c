/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 22:22:31 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 23:48:15 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_pipe.h"

/*
** If the pipe doesn't already exist, the list of connected nodes of each of the
** two node is completed with the other one
*/

static t_bool	ft_pipe2(t_list *head1, t_list *head2)
{
	t_list	*check_dup;

	check_dup = ((t_node*)head2->content)->pipes;
	while (check_dup)
	{
		if (check_dup->content == head1->content)
			return (TRUE);
		check_dup = check_dup->next;
	}
	if (head1->content == head2->content)
		return (TRUE);
	ft_lstadd(&((t_node*)head1->content)->pipes,\
		ft_lstnew_p(head2->content, sizeof(t_node)));
	ft_lstadd(&((t_node*)head2->content)->pipes,\
		ft_lstnew_p(head1->content, sizeof(t_node)));
	return (TRUE);
}

/*
** Parse le input encoding for the pipes.
** If the format is OK, keep the pipe in mind and return True
*/

t_bool			ft_pipe(t_anthill *anthill, char *line)
{
	int		i;
	t_list	*head1;
	t_list	*head2;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	if (line[i] == '\0')
		return (FALSE);
	line[i] = '\0';
	head1 = anthill->nodes;
	while (head1 && ft_strcmp(((t_node*)head1->content)->name, line))
		head1 = head1->next;
	if (!head1)
		return (FALSE);
	head2 = anthill->nodes;
	while (head2 && ft_strcmp(((t_node*)head2->content)->name, &line[i + 1]))
		head2 = head2->next;
	if (!head2)
		return (FALSE);
	line[i] = '-';
	return (ft_pipe2(head1, head2));
}
