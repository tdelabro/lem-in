/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:17:29 by tdelabro          #+#    #+#             */
/*   Updated: 2019/11/30 11:25:52 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include "t_anthill.h"
# include "t_combi.h"
# include <unistd.h>

t_anthill	*ft_parse(void);
t_list		*ft_generate_paths(t_anthill *anthill);
void		ft_free_list_but_content(void *lst);
void		ft_print_anthill(t_list *combis);
void		ft_free_combi(t_list **combi);

#endif
