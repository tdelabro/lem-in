/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:35:05 by tdelabro          #+#    #+#             */
/*   Updated: 2019/11/14 17:02:44 by tdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstjoin(t_list **alst, t_list *new)
{
	t_list *head;

	if (alst && new)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			head = *alst;
			while (head->next)
				head = head->next;
			head->next = new;
		}
	}
}
