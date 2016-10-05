/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 17:27:01 by jblondea          #+#    #+#             */
/*   Updated: 2015/12/10 14:53:32 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **begin_list, void *data, size_t content_size)
{
	t_list	*tmp;
	t_list	*start;

	start = *begin_list;
	if (start)
	{
		tmp = ft_lstnew(data, content_size);
		while (start->next)
			start = start->next;
		start->next = tmp;
	}
	else
	{
		*begin_list = ft_lstnew(data, content_size);
	}
}
