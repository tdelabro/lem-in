/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_paths.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:37:35 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 22:06:16 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATE_PATHS_H
# define GENERATE_PATHS_H

# include "libft.h"
# include "t_anthill.h"
# include "t_node.h"
# include "t_combi.h"
# include "ft_printf.h"

void	ft_free_list_but_content(void *lst);
t_list	*ft_node_is_in_lst(t_list *lst, t_node *node);
void	ft_set_pipes_unavailable(t_list *path);
void	ft_restore_pipes(t_list *path);
void	ft_create_t_combi(t_list **combi, t_list **used_paths, int *tab_n_ants);
void	ft_get_tab_n_ants(t_list *combi, int **tab_n_ants, int n_ants);
t_list	*ft_bfs(t_anthill *anthill, t_list *used_paths);
t_list	*ft_combine_paths(t_list *paths);
t_list	*ft_get_used_nodes(t_list *combi);
void	ft_free_combi(t_list **combi);
t_bool	ft_check_overlap(t_list *paths);
void	ft_list_paths(t_anthill *anthill, t_list **combis, t_list **used_paths);

#endif
