/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_combi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:56:26 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 23:57:03 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_combi.h"

/*
** Simply calculate the number of turn the combi will take to finish the anthill
** It's equal to the numver of ants we have to send into the longest used path
*/

static int		ft_calcul_score(t_list *used_paths, int *tab_n_ants, int len)
{
	int		i;
	t_list	*head;
	int		max;
	int		tmp;

	max = 0;
	i = 0;
	head = used_paths;
	while (i < len)
	{
		if (tab_n_ants[i] > 0 \
			&& (tmp = ft_lstlen(head->content) + tab_n_ants[i] - 2) > max)
			max = tmp;
		i++;
		head = head->next;
	}
	return (max);
}

/*
** Duplicate the list of used_paths
** This way we can continue to use the original while searching for other combis
** and free them independently
*/

static t_list	*ft_duplicate_combi(t_list *combi)
{
	t_list	*head;
	t_list	*new;

	new = NULL;
	head = combi;
	while (head)
	{
		ft_lstappend(&new, \
				ft_lstnew_p(ft_lstdup_p(head->content), sizeof(t_list)));
		head = head->next;
	}
	return (new);
}

/*
** If it's the first combi to be found or if the new combi is better than the
** ones we already found, alocate memory for a t_combi struct and fill it with
** the needed infos :
** .paths	list of the paths part of this combi
** .len		number of paths in this combi
** .tab		contain the number of ant to send in each path
** .score	the number of turn this combi will take to resolve the anthill
*/

void			ft_create_t_combi(t_list **combi, t_list **used_paths, \
					int *tab_n_ants)
{
	t_combi	*new;
	int		score;
	int		len;

	len = ft_lstlen(*used_paths);
	if (!*combi || len < ((t_combi*)(*combi)->content)->len)
	{
		score = ft_calcul_score(*used_paths, tab_n_ants, len);
		if (*combi && score >= ((t_combi*)(*combi)->content)->score)
			return ;
		if (!(new = (t_combi*)malloc(sizeof(t_combi))))
			return ;
		new->paths = ft_duplicate_combi(*used_paths);
		new->len = len;
		new->tab = tab_n_ants;
		new->score = score;
		ft_lstadd(combi, ft_lstnew_p(new, sizeof(t_combi)));
	}
}
