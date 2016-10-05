/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 01:49:33 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/13 01:54:25 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstfree(t_list *lst)
{
	if (lst)
	{
		if (lst->content)
			free(lst->content);
		if (lst->next)
			ft_lstfree(lst->next);
		free(lst);
		lst = NULL;
	}
}
