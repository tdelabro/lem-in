/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:18:21 by tdelabro          #+#    #+#             */
/*   Updated: 2019/11/30 09:35:02 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_NODE_H
# define T_NODE_H

# include "libft.h"

typedef struct	s_node
{
	char	*name;
	t_list	*pipes;
	t_list	*available_pipes;
}				t_node;

#endif
