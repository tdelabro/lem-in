/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:42:37 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 19:06:54 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_anthill.h"

/*
** Free the ant and the node containing it. Remove it from the list of ants.
*/

void			ft_del_ant(t_list **ants, t_list **head, t_list **prev)
{
	t_list	*tmp;

	if (!((t_ant*)(*head)->content)->room->next)
	{
		tmp = *head;
		*head = (*head)->next;
		if (!(*prev))
			*ants = (*ants)->next;
		else
			(*prev)->next = tmp->next;
		free(tmp->content);
		free(tmp);
	}
	else
	{
		*prev = *head;
		*head = (*head)->next;
	}
}

/*
** Go throug the list of t_ants and make every one of them moove to the next
** room while printing the coresponding moove on stdout.
*/

static void		ft_one_step_beyond(t_list **ants)
{
	t_bool	first_moove;
	t_list	*head;
	t_list	*prev;

	first_moove = TRUE;
	head = *ants;
	prev = NULL;
	while (head)
	{
		((t_ant*)head->content)->room = ((t_ant*)head->content)->room->next;
		if (first_moove)
		{
			ft_printf("L%d-%s", ((t_ant*)head->content)->id, \
					((t_node*)((t_ant*)head->content)->room->content)->name);
			first_moove = FALSE;
		}
		else
			ft_printf(" L%d-%s", ((t_ant*)head->content)->id, \
					((t_node*)((t_ant*)head->content)->room->content)->name);
		ft_del_ant(ants, &head, &prev);
	}
	write(1, "\n", 1);
}

/*
** Create the t_ant struc dedicated to one ant, going through one specific path
*/

static void		ft_introduce_ant(t_list **ants, t_list *path)
{
	t_ant		new;
	static int	num_ant = 1;

	new.id = num_ant++;
	new.room = path;
	ft_lstappend(ants, ft_lstnew(&new, sizeof(t_ant)));
}

/*
** The last combi we added to the list is the fastest. We select it and proceed.
** combi->tab cntain the number of ant we have to send in each path.
** Ex: Ã12, 9, 3, 1, 1]
** We go through it, creating a new ant attached to each path and reducing by 1
** the remaining number of ant to go into this path.
** Each time we reach the end of the tab or an int set to 0, we procced to make
** every exiting ant moove one step further, and we start again at the begining
** of the tab.
** When all int in the tab are equal to 0. We make ants moove forwards until
** they all reached the ending node.
*/

void			ft_print_anthill(t_list *combis)
{
	int		i;
	t_list	*head;
	t_list	*ants;
	t_combi	*combi;

	ants = NULL;
	i = -1;
	combi = combis->content;
	head = combi->paths;
	while (ft_sum_tab(combi->tab, combi->len) > 0)
	{
		if (++i == combi->len && !(i = 0))
		{
			ft_one_step_beyond(&ants);
			head = combi->paths;
		}
		if (combi->tab[i] > 0)
		{
			combi->tab[i]--;
			ft_introduce_ant(&ants, head->content);
		}
		head = head->next;
	}
	while (ants)
		ft_one_step_beyond(&ants);
}
