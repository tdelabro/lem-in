/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:22:04 by tdelabro          #+#    #+#             */
/*   Updated: 2019/11/29 16:23:29 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PIPE_H
# define T_PIPE_H

# include "t_node.h"

typedef struct	s_pipe
{
	t_node			*node;
	struct s_pipe	*parent;
}				t_pipe;

#endif
