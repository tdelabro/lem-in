/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:37:21 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 15:10:18 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generate_paths.h"

/*
** 4 diferents situation:
**	- the used_paths are or are not overlapping
**	- the new path we just added does or doesn't improove the combination
**		(too loong in comparaison to the small number of ants in the anthill)
**
** If the paths are overlaping we create a new path combination wich is not,
** base on those paths, using ft_combine_paths, on wich we act normaly.
** If the new path is not used by any ant we call it a valid combination and
** store it into the appropriate list, otherwise we ccontinue the recursion.
*/

static void	ft_take_action(t_anthill *anthill, t_list **combis, \
										t_list **used_paths, int *tab_n_ants)
{
	t_list *tmp;

	if (!ft_check_overlap(*used_paths))
	{
		ft_get_tab_n_ants(*used_paths, &tab_n_ants, anthill->ant);
		if (tab_n_ants[0] <= 0)
			ft_create_t_combi(combis, used_paths, tab_n_ants);
		else
		{
			free(tab_n_ants);
			ft_list_paths(anthill, combis, used_paths);
		}
	}
	else if ((tmp = ft_combine_paths(*used_paths)))
	{
		ft_get_tab_n_ants(tmp, &tab_n_ants, anthill->ant);
		if (tab_n_ants[0] <= 0)
			ft_create_t_combi(combis, &tmp, tab_n_ants);
		else
		{
			free(tab_n_ants);
			ft_list_paths(anthill, combis, &tmp);
		}
		ft_free_combi(&tmp);
	}
}

/*
** Delete the new_path we just added to used used_paths, allowing us to test the
** following in the next loop iteration
*/

static void	ft_del_tested_path(t_list **used_paths)
{
	t_list	*tmp;

	tmp = *used_paths;
	*used_paths = (*used_paths)->next;
	free(tmp);
}

/*
** Inputs:	the t_anhill* containing everyhing we need to find the combi,
**			two pointers on NULL list:
**				- combis, to store valid combinations of paths
**				- used_paths, wich is constantly updated with new combinations
**
** The function is called recursively with updated used_paths and
** available_pipes, untill ft_bfs is unable to find new paths.
**
** ft_bfs return list of all the new paths of same minimal lenght we can add to
** this particular state of used_paths.
** This list is traversed and each of it's paths is added one after the other to
** used paths.
** Each time one paths is added we either store it as a valid combination,
** or call recursively ft_list_paths with this updated used_paths and pipes.
*/

void		ft_list_paths(t_anthill *anthill, t_list **combis,\
														t_list **used_paths)
{
	t_list	*new_paths;
	t_list	*head;
	int		*tab_n_ants;

	tab_n_ants = NULL;
	new_paths = ft_bfs(anthill, *used_paths);
	if (new_paths == NULL && *used_paths)
	{
		ft_get_tab_n_ants(*used_paths, &tab_n_ants, anthill->ant);
		ft_create_t_combi(combis, used_paths, tab_n_ants);
	}
	else
	{
		head = new_paths;
		while (head)
		{
			ft_set_pipes_unavailable(head->content);
			ft_lstadd(used_paths, ft_lstnew_p(head->content, sizeof(t_list)));
			ft_take_action(anthill, combis, used_paths, tab_n_ants);
			ft_restore_pipes(head->content);
			head = head->next;
			ft_del_tested_path(used_paths);
		}
	}
	ft_free_combi(&new_paths);
}

/*
** Input : the t_anthill* struct
** Output : A list of different combination of paths we found
**	ie. a list of lists of nodes
*/

t_list		*ft_generate_paths(t_anthill *anthill)
{
	t_list	*combis;
	t_list	*used_paths;

	combis = NULL;
	used_paths = NULL;
	ft_list_paths(anthill, &combis, &used_paths);
	ft_free_list_but_content(&used_paths);
	return (combis);
}
