/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 22:48:32 by tdelabro          #+#    #+#             */
/*   Updated: 2019/08/07 23:04:51 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup_p(t_list *lst)
{
	t_list	*head;
	t_list	*new;

	new = NULL;
	head = lst;
	while (head)
	{
		ft_lstadd(&new, ft_lstnew_p(head->content, head->content_size));
		head = head->next;
	}
	ft_lstrev(&new);
	return (new);
}
