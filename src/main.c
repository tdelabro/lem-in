/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:15:40 by lmariott          #+#    #+#             */
/*   Updated: 2019/12/02 22:48:41 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Free the node stuctures and it's variables
*/

static void	ft_free_node(t_node *node)
{
	ft_memdel((void**)&node->name);
	ft_free_list_but_content(&node->pipes);
	ft_free_list_but_content(&node->available_pipes);
	ft_memdel((void**)&node);
}

/*
** Free every nodes in every paths in the combi
*/

static void	ft_free_combis(t_list **combis)
{
	t_list	*head;
	t_list	*tmp;

	head = *combis;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free_combi(&((t_combi*)tmp->content)->paths);
		free(((t_combi*)tmp->content)->tab);
		free(tmp->content);
		free(tmp);
	}
	*combis = NULL;
}

/*
** Free every variable of an anthill struct and the struct itself
*/

static int	ft_free_anthill(t_anthill **anthill)
{
	t_list	*head;
	t_list	*tmp;

	head = (*anthill)->nodes;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free_node(tmp->content);
		free(tmp);
	}
	ft_memdel((void**)anthill);
	return (0);
}

/*
** ft_parse() create an anthill struct storing every node of the anthill
** We the initialize the available_pipes t_list* variable for each node
** ft_generate_paths() give us a list of every combination of the algo found
** ft_print_anthill() select the best combination and proceed to moove the ants
*/

int			main(int ac, char **av)
{
	t_anthill	*anthill;
	t_list		*combis;
	t_list		*head;

	if (!(ac && av[0]) || !(anthill = ft_parse()) \
			|| !anthill->nodes || !anthill->start || !anthill->end)
		return (write(1, "ERROR\n", 6));
	if (anthill->start == anthill->end)
		return (ft_free_anthill(&anthill));
	head = anthill->nodes;
	while (head)
	{
		((t_node*)head->content)->available_pipes =\
			ft_lstdup_p(((t_node*)head->content)->pipes);
		head = head->next;
	}
	if (!(combis = ft_generate_paths(anthill)))
		return (write(1, "ERROR\n", 6));
	ft_print_anthill(combis);
	ft_free_combis(&combis);
	return (ft_free_anthill(&anthill));
}
