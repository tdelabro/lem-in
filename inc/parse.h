/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:22:33 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 20:45:54 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "t_node.h"
# include "t_anthill.h"

t_bool	ft_node(t_anthill *anthill, const char *line, uint8_t *p_mode);
t_bool	ft_pipe(t_anthill *anthill, const char *line);

#endif
