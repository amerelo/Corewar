/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 02:19:11 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/08 20:15:32 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 4096

typedef struct	s_gnl
{
	char			*str;
	int				fd;
	struct s_gnl	*next;
}				t_gnl;

typedef struct	s_helper
{
	void	**buf;
}				t_helper;

int				get_next_line(const int fd, char **line);

#endif
