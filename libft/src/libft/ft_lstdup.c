/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:19:33 by tdelabro          #+#    #+#             */
/*   Updated: 2019/12/01 23:19:39 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*head;
	t_list	*new;

	new = NULL;
	head = lst;
	while (head)
	{
		ft_lstadd(&new, ft_lstnew(head->content, head->content_size));
		head = head->next;
	}
	ft_lstrev(&new);
	return (new);
}
