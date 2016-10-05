/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 04:48:24 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/08 20:14:35 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		initialize_helper(t_helper **helper)
{
	int		i;

	if (!(*helper = malloc(sizeof(t_helper))))
		return (-1);
	if (!((*helper)->buf = malloc(sizeof(void *) * 1024)))
		return (-1);
	i = -1;
	while (++i < 1024)
		(*helper)->buf[i] = ft_strnew(0);
	return (1);
}

void	update_helper(int const fd, t_helper *helper, char *buffer)
{
	void			*tmp;

	if (buffer)
	{
		tmp = helper->buf[fd];
		helper->buf[fd] = ft_strjoin(tmp, buffer);
		ft_memdel(&tmp);
	}
}

int		eval_new_cont(int const fd, char **line, t_helper *helper, char *buffer)
{
	void			*tmp;
	char			*find;
	char			*prev;

	update_helper(fd, helper, buffer);
	prev = (char *)helper->buf[fd];
	find = ft_strchr(prev, '\n');
	tmp = helper->buf[fd];
	if (find)
	{
		*line = ft_strsub(prev, 0, find - prev);
		helper->buf[fd] = ft_strsub(tmp, ft_strlen(*line) + 1,
									ft_strlen(prev) - ft_strlen(*line));
		ft_memdel(&tmp);
		return (1);
	}
	if (!find && prev[0] && !buffer)
	{
		*line = ft_strdup(tmp);
		ft_memdel(&tmp);
		helper->buf[fd] = ft_strnew(0);
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static t_helper	*helper;
	char			buffer[BUFF_SIZE + 1];
	int				k;

	if (!line)
		return (-1);
	if (!helper)
		if (initialize_helper(&helper) < 0)
			return (-1);
	while ((k = read(fd, buffer, BUFF_SIZE)))
	{
		if (k > 0)
		{
			buffer[k] = 0;
			k = eval_new_cont(fd, line, helper, buffer);
			if (k)
				return (k);
		}
		else
			return (-1);
	}
	return (eval_new_cont(fd, line, helper, NULL));
}
