/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ant.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:01:01 by tdelabro          #+#    #+#             */
/*   Updated: 2019/09/01 15:04:43 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ANT_H
# define T_ANT_H

# include "t_node.h"
# include "libft.h"

typedef struct	s_ant
{
	int		id;
	t_list	*room;
}				t_ant;

#endif
