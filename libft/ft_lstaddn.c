/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 01:21:17 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/30 01:35:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddn(t_list **lst, size_t n, t_list *new)
{
	*lst = ft_lstgetn(lst, n);
	if (*lst)
	{
		new->next = (*lst)->next;
		(*lst)->next = new;
	}
}
