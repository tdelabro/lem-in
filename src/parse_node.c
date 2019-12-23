/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 22:05:40 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/02 23:43:37 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_node.h"

/*
** Create a new node struct, add it to the list anthill->rooms
** If the room is suposed to be the start or the end, we keep trace of it in
** the anthill struct
*/

static t_bool	ft_save_node(t_anthill *anthill, t_node node, uint8_t *p_mode)
{
	if ((*p_mode & 0x80 && anthill->start) || (*p_mode & 0x40 && anthill->end))
	{
		ft_memdel((void**)node.name);
		return (FALSE);
	}
	ft_lstadd(&anthill->nodes, ft_lstnew(&node, sizeof(t_node)));
	if (*p_mode & 0x80)
		anthill->start = ((t_list*)anthill->nodes)->content;
	if (*p_mode & 0x40)
		anthill->end = ((t_list*)anthill->nodes)->content;
	return (TRUE);
}

/*
** Parse the line. If the syntax is OK, create a new node and return TRUE
*/

t_bool			ft_node(t_anthill *anthill, const char *line, uint8_t *p_mode)
{
	t_node		node;
	int			i;
	t_bool		ret;

	if ((i = -1) && line[0] == 'L')
		return (FALSE);
	while ((ret = TRUE) && line[++i] != ' ')
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (FALSE);
	ft_bzero(&node, sizeof(t_node));
	node.name = ft_strndup(line, i);
	while (line[++i] != ' ')
		if (ft_isdigit(line[i]) == 0 && line[i] != '-')
			ret = FALSE;
	while (line[++i])
		if (ft_isdigit(line[i]) == 0 && line[i] != '-')
			ret = FALSE;
	if (!ft_save_node(anthill, node, p_mode))
		ret = FALSE;
	*p_mode = (*p_mode | 0xC0) ^ 0xC0;
	if (ret == FALSE)
		ft_memdel((void**)node.name);
	return (ret);
}
