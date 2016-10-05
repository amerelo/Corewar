/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:17:14 by jblondea          #+#    #+#             */
/*   Updated: 2016/07/24 23:49:08 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

void	add_head(t_asm *p_box, int fd, int dis, int dis2)
{
	char	head[4];
	char	size[4];
	int		unused __attribute__((unused));

	head[0] = 0;
	head[1] = 234;
	head[2] = 131;
	head[3] = 243;
	unused = write(fd, head, 4);
	unused = write(fd, p_box->head.prog_name, ft_strlen(p_box->head.prog_name));
	dis -= (ft_strlen(p_box->head.prog_name) > 0) ?
	ft_strlen(p_box->head.prog_name) : 0;
	while (--dis)
		unused = write(fd, head, 1);
	size[0] = (p_box->champ_size & 0xff000000) >> 24;
	size[1] = (p_box->champ_size & 0x00ff0000) >> 16;
	size[2] = (p_box->champ_size & 0x0000ff00) >> 8;
	size[3] = p_box->champ_size & 0x000000ff;
	unused = write(fd, size, 4);
	unused = write(fd, p_box->head.comment, ft_strlen(p_box->head.comment));
	dis2 -= (ft_strlen(p_box->head.comment) > 0) ?
	ft_strlen(p_box->head.comment) : 0;
	while (--dis2)
		unused = write(fd, head, 1);
}

void	write_champ(t_asm *parsed_champ)
{
	int		fd;
	char	*dir;
	t_list	*tmp;
	int		unused __attribute__((unused));

	tmp = parsed_champ->elements;
	dir = ft_strjoin(parsed_champ->file_name, ".cor");
	fd = open(dir, O_CREAT | O_RDWR | O_TRUNC, 0777);
	add_head(parsed_champ, fd, 133, 2053);
	while (tmp)
	{
		if (tmp->content_size == sizeof(t_instruction))
			unused = write(fd, ((t_instruction*)(tmp->content))->hexdump,
			(size_t)((t_instruction*)(tmp->content))->size);
		tmp = tmp->next;
	}
	ft_printf("Writing output program to %s\n", dir);
	free(dir);
}
