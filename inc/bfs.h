/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:33:42 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 23:08:21 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BFS_H
# define BFS_H

# include "libft.h"
# include "t_anthill.h"
# include "t_node.h"
# include "t_combi.h"
# include "t_pipe.h"

t_list	*ft_node_is_in_lst(t_list *lst, t_node *node);
void	ft_free_list_but_content(void *lst);
t_list	*ft_get_used_nodes(t_list *paths);
t_list	*ft_get_all_equal_paths(t_anthill *anthill, t_list *pipes);
t_bool	ft_has_been_visited(t_list *pipes, t_node *node);

#endif
