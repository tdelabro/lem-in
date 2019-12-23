/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_during_bfs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:40:42 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 18:12:27 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_DURING_BFS_H
# define CONTROL_DURING_BFS_H

# include "libft.h"
# include "t_node.h"

t_list	*ft_combine_paths(t_list *paths, t_list *used);
void	ft_free_combi(t_list **combi);
t_list	*ft_node_is_in_lst(t_list *lst, t_node *node);
void	ft_get_tab_n_ants(t_list *combi, int **tab_n_ants, int n_ants);

#endif
