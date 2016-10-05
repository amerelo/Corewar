/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:55:38 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/29 21:38:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *lst1, t_list *lst2)
{
	void	*tmp;
	size_t	tmp_size;

	tmp = lst2->content;
	tmp_size = lst2->content_size;
	lst2->content = lst1->content;
	lst2->content_size = lst1->content_size;
	lst1->content = tmp;
	lst1->content_size = tmp_size;
}
