/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_anthill.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 11:24:15 by lmariott          #+#    #+#             */
/*   Updated: 2019/11/30 09:51:54 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ANTHILL_H
# define T_ANTHILL_H

# include "t_node.h"

typedef struct			s_anthill
{
	int		ant;
	int		rooms;
	t_node	*start;
	t_node	*end;
	t_list	*nodes;
}						t_anthill;

#endif
