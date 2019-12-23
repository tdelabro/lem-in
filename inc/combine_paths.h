/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_paths.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:39:28 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 20:30:20 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMBINE_PATHS_H
# define COMBINE_PATHS_H

# include "libft.h"
# include "t_node.h"

int		ft_get_index(t_list *used, t_node *node);
t_node	*ft_get_node(t_list *used, int index);
t_bool	**ft_init_tab(int size);
t_bool	**ft_del_tab(t_bool **tab, int size);
void	ft_free_list_but_content(void *lst);
t_list	*ft_get_used_nodes(t_list *combi);
t_bool	ft_node_is_in_lst(t_list *path, t_node *node);
void	ft_free_combi(t_list **combi);
t_list	*ft_get_new_paths(t_bool **tab, t_list *used);
void	ft_sort_paths_by_length(t_list **paths);
void	ft_eliminate_passing(t_bool **tab, int size);

#endif
