/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:24:54 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/26 20:28:32 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_magic(int fd)
{
	char	buffer[5];

	if (read(fd, buffer, 4) < 4)
		error(8);
	if (buffer[0])
		error(8);
	if (buffer[1] != (char)((COREWAR_EXEC_MAGIC & 0xff0000) >> 16))
		error(8);
	if (buffer[2] != (char)((COREWAR_EXEC_MAGIC & 0xff00) >> 8))
		error(8);
	if (buffer[3] != (char)(COREWAR_EXEC_MAGIC & 0xff))
		error(8);
}

static void	set_champion_head(int fd, t_player *p)
{
	unsigned char	buffer[COMMENT_LENGTH + 5];

	if (read(fd, buffer, PROG_NAME_LENGTH + 4) < PROG_NAME_LENGTH + 4)
		error(8);
	if (!(p->name = ft_strnew(PROG_NAME_LENGTH + 5)))
		error(6);
	ft_memcpy(p->name, buffer, PROG_NAME_LENGTH + 4);
	if (read(fd, buffer, 4) < 4)
		error(8);
	if ((p->size = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8)
			| buffer[3]) > CHAMP_MAX_SIZE)
		error(8);
	if (read(fd, buffer, COMMENT_LENGTH + 4) < COMMENT_LENGTH + 4)
		error(8);
	if (!(p->comment = ft_strnew(COMMENT_LENGTH + 5)))
		error(6);
	ft_memcpy(p->comment, buffer, COMMENT_LENGTH + 4);
	if (read(fd, buffer, p->size + 1) != p->size)
		error(9);
	if (!(p->champion = ft_strnew(p->size)))
		error(6);
	ft_memcpy(p->champion, buffer, p->size);
}

static void	new_champion(char *av, int n, t_vm *vm)
{
	t_player	*current;
	t_player	*new;
	int			fd;

	current = vm->players;
	if ((fd = open(av, O_RDONLY)) == -1)
		error(7);
	check_magic(fd);
	while (current)
		if (n != -1 && current->number == n)
			error(5);
		else if (current->next)
			current = current->next;
		else
			break ;
	if (!(new = (t_player*)ft_memalloc(sizeof(t_player))))
		error(6);
	new->number = n;
	new->lives = 0;
	new->last_live = 0;
	new->next = NULL;
	set_champion_head(fd, new);
	current ? (current->next = new)
		: (vm->players = new);
}

static void	set_champion(int ac, char **av, int *index, t_vm *vm)
{
	int			n;
	int			fd;

	n = -1;
	if (!ft_strcmp(av[*index], "-n"))
	{
		*index += 1;
		if (*index >= ac)
			error(3);
		if ((fd = open(av[*index], O_RDONLY)) == -1)
		{
			ft_strlen(av[*index]) > 10 ? error(4) : 0;
			if ((n = ft_atoi(av[*index])) < 1)
				error(4);
			if ((*index += 1) >= ac)
				error(10);
		}
	}
	new_champion(av[*index], n, vm);
}

void		check_args(int ac, char **av, t_vm *vm)
{
	int	index;

	index = 0;
	while (++index < ac)
		if (!ft_strcmp(av[index], "-g"))
			vm->flags |= VM_GRAPH;
		else if (!ft_strcmp(av[index], "-a"))
			vm->flags |= VM_HIDE_AFF;
		else if (!ft_strcmp(av[index], "-c"))
			vm->flags |= VM_DUMP_COLOR;
		else if (!ft_strcmp(av[index], "-h"))
			vm->flags |= VM_HIDE;
		else if (!ft_strcmp(av[index], "-64"))
			vm->flags |= VM_64;
		else if (!ft_strcmp(av[index], "-dump"))
		{
			vm->flags |= VM_DUMP;
			++index;
			index >= ac || ft_strlen(av[index]) > 10 ? error(12) : 0;
			index >= ac || (*av[index] < '0' || *av[index] > '9')
				? error(2) : (vm->dump = ft_atoi(av[index]));
			vm->dump < 0 ? error(12) : 0;
		}
		else if (index < ac)
			set_champion(ac, av, &index, vm);
}
