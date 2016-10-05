/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:07:13 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/24 23:25:19 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"

int			main(int ac, char **av)
{
	t_vm	vm;
	int		total;

	if (ac < 2)
		error(1);
	init_vm(&vm);
	check_args(ac, av, &vm);
	if ((total = count_list(vm.players)) > MAX_PLAYERS)
		error(11);
	if (!total)
		error(10);
	while (set_num(&vm))
		;
	ft_printf("Introducing contestants...\n");
	aff_champions(&vm, total);
	if (vm.flags & VM_GRAPH)
		launch_gui(&vm);
	else
	{
		let_the_game_begin(&vm, NULL);
		and_the_winner_is(&vm);
		free_champions(&vm.players);
	}
	return (0);
}

int			count_list(t_player *c)
{
	int		counter;

	counter = 0;
	while (c)
	{
		counter += 1;
		c = c->next;
	}
	return (counter);
}

void		init_vm(t_vm *vm)
{
	vm->flags = 0;
	vm->dump = 0;
	vm->cycles = 0;
	vm->process = NULL;
	vm->players = NULL;
	vm->lives = 0;
	vm->period = 0;
	vm->f[0] = &c_live;
	vm->f[1] = &c_ld;
	vm->f[2] = &c_st;
	vm->f[3] = &c_add;
	vm->f[4] = &c_sub;
	vm->f[5] = &c_and;
	vm->f[6] = &c_or;
	vm->f[7] = &c_xor;
	vm->f[8] = &c_zjmp;
	vm->f[9] = &c_ldi;
	vm->f[10] = &c_sti;
	vm->f[11] = &c_fork;
	vm->f[12] = &c_lld;
	vm->f[13] = &c_lldi;
	vm->f[14] = &c_lfork;
	vm->f[15] = &c_aff;
	ft_bzero(vm->memory, MEM_SIZE);
	ft_bzero(vm->color, MEM_SIZE);
}

static void	error_bis(int n)
{
	if (n == 7)
		ft_putstr_fd("Error : file not found.\n", 2);
	else if (n == 8)
		ft_putstr_fd("Error : input is not a valid file.\n", 2);
	else if (n == 2)
		ft_putstr_fd("Error : nbr_cycles not set after -dump.\n", 2);
	else if (n == 12)
		ft_putstr_fd("Error : bad number set after -dump.\n", 2);
	else if (n == 9)
	{
		ft_putstr_fd("Error : champion size differ from what its internal ", 2);
		ft_putstr_fd("header says.\n", 2);
	}
	else if (n == 10)
		ft_putstr_fd("Error : no champion set.\n", 2);
	else if (n == 11)
		ft_putstr_fd("Error : too much champions set.\n", 2);
}

void		error(int n)
{
	if (n == 1)
	{
		ft_putstr("Usage:\t./corewar [-gcnh][-64][-dump nbr_cycles]");
		ft_putstr(" <[-n champ_num] champion.cor> <...>\n\n");
		ft_putstr(" -g\t\t\t\t: set graphical user interface.\n");
		ft_putstr(" -h\t\t\t\t: hide lives display.\n");
		ft_putstr(" -a\t\t\t\t: hide affs display.\n");
		ft_putstr(" -n <champ_num> <champion>\t: set a personnal number to");
		ft_putstr(" next champion.\n -dump <nbr_cycles>\t\t: dump memory");
		ft_putstr(" state at <nbr_cycles> cycle to standard output.\n");
		ft_putstr("\t| -c\t\t\t: set color mode for [-dump].\n");
		ft_putstr("\t| -64\t\t\t: set 64 bytes display mode for [-dump].\n");
	}
	else if (n == 3)
		ft_putstr_fd("Error : there is no arguments after -n.\n", 2);
	else if (n == 4)
		ft_putstr_fd("Error : bad champion number.\n", 2);
	else if (n == 5)
		ft_putstr_fd("Error : duplication of champion number.\n", 2);
	else if (n == 6)
		ft_putstr_fd("Error : memory allocation failed.\n", 2);
	else
		error_bis(n);
	exit(1);
}
