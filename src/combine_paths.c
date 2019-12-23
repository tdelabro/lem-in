/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:35:19 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 20:35:56 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "combine_paths.h"

/*
** We drow a two dimension tab of boolean. Eaach node is present two times,
** once in the rows, and once in the columns.
**
** Her is the tab representation of the two folowing paths :
**	Start - A - B - End
**	Start - C - B - A - D - End
**
**		Start	A	B	End	C	D
** Start	0	1	0	0	1	0	From Start ants goes to A and C
** A		0	0	1	0	0	1
** B		0	1	0	1	0	0
** C		0	0	1	0	0	0
** D		0	0	0	1	0	0
** End		0	0	0	0	0	0	No ant leave End
**
** If the same pipe is used in the two directions, we toogle the two case to 0 :
**
**		Start	A	B	End	C	D
** Start	0	1	0	0	1	0	From Start ants goes to A and C
** A		0	0	X	0	0	1
** B		0	X	0	1	0	0
** C		0	0	1	0	0	0
** D		0	0	0	1	0	0
** End		0	0	0	0	0	0	No ant leave End
**
** Then we can travel the new tab from start, creating new paths :
**	Start - A - D - End
**	Start - C - B - End
*/

static t_list	*ft_combine_overlapping_paths(t_list *paths, t_list *used)
{
	t_bool	**tab;
	t_list	*head1;
	t_list	*head2;
	int		nb_nodes;
	t_list	*ret;

	nb_nodes = ft_lstlen(used);
	tab = ft_init_tab(ft_lstlen(used));
	head1 = paths;
	while (head1)
	{
		head2 = head1->content;
		while (head2->next)
		{
			tab[ft_get_index(used, head2->content)]\
				[ft_get_index(used, head2->next->content)] = TRUE;
			head2 = head2->next;
		}
		head1 = head1->next;
	}
	ft_eliminate_passing(tab, ft_lstlen(used));
	ret = ft_get_new_paths(tab, used);
	ft_free_list_but_content(&used);
	ft_del_tab(tab, nb_nodes);
	return (ret);
}

/*
** Take the whole combi and split it into two new ones :
** - paths that doesn't overlap are duplicated
** - paths that does are stored for later treatment
*/

void			ft_split_paths(t_list *paths, t_list **new_paths, \
													t_list **overlapping_paths)
{
	t_list	*head_paths;
	t_list	*head_nodes;

	head_paths = paths->next;
	while (head_paths)
	{
		head_nodes = ((t_list*)head_paths->content)->next;
		while (head_nodes->next)
		{
			if (ft_node_is_in_lst(paths->content, head_nodes->content))
			{
				ft_lstadd(overlapping_paths, ft_lstnew_p(\
							ft_lstdup_p(head_paths->content), sizeof(t_list)));
				break ;
			}
			head_nodes = head_nodes->next;
		}
		if (!head_nodes->next)
			ft_lstadd(new_paths, \
				ft_lstnew_p(ft_lstdup_p(head_paths->content), sizeof(t_list)));
		head_paths = head_paths->next;
	}
	ft_lstadd(overlapping_paths, \
			ft_lstnew_p(ft_lstdup_p(paths->content), sizeof(t_list)));
}

/*
** Create a new combi based on the overlapping one.
*** The paths which aren't concerned by the overlapping are just duplicated,
** those who are give bith to new paths
*/ 

t_list			*ft_combine_paths(t_list *paths)
{
	t_list	*new_paths;
	t_list	*overlapping_paths;

	new_paths = NULL;
	overlapping_paths = NULL;
	ft_split_paths(paths, &new_paths, &overlapping_paths);
	ft_lstjoin(&new_paths, ft_combine_overlapping_paths(overlapping_paths, \
										ft_get_used_nodes(overlapping_paths)));
	ft_sort_paths_by_length(&new_paths);
	ft_free_combi(&overlapping_paths);
	return (new_paths);
}
