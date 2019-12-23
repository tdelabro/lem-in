/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_combi.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:01:01 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 18:00:44 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMBI_H
# define T_COMBI_H

# include "libft.h"

typedef struct	s_combi
{
	t_list		*paths;
	int			len;
	int			*tab;
	int			score;
}				t_combi;

#endif
