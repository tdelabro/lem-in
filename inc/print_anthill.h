/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:58:25 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 17:58:06 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ANTHILL_H
# define PRINT_ANTHILL_H

# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "t_ant.h"
# include "t_combi.h"

int		ft_sum_tab(int *tab, int len);
void	ft_free_combi(t_list **combi);

#endif
