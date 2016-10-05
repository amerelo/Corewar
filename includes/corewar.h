/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:08:46 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/23 04:27:54 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "libft.h"
# include "op.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define VM_DUMP		0x01
# define VM_GRAPH		0x02
# define VM_DUMP_COLOR	0x04
# define VM_REFRESH		0x08
# define VM_HIDE		0x10
# define VM_64			0x20
# define VM_HIDE_AFF	0x40

# define P_CARRY	0x01
# define P_LIVE		0x02
# define P_INDEX	0x04
# define P_I_CARRY	0x08
# define P_IDX_MOD	0x10

typedef struct	s_process
{
	struct s_process	*next;
	int					reg[REG_NUMBER];
	int					pc;
	int					cycles;
	int					player;
	unsigned int		flags;
	unsigned char		opcode;
}				t_process;

typedef struct	s_player
{
	struct s_player	*next;
	char			*name;
	char			*comment;
	char			*champion;
	int				lives;
	int				curr_p_lives;
	int				last_live;
	int				number;
	char			index;
	unsigned int	size;
	int				color;
	int				color_hl;
}				t_player;

typedef struct	s_vm
{
	int				flags;
	int				dump;
	int				cycles;
	int				pl;
	int				lives;
	int				period;
	t_process		*process;
	t_player		*players;
	int				(*f[16])(struct s_vm*, t_process*);
	unsigned char	memory[MEM_SIZE];
	char			color[MEM_SIZE];
}				t_vm;

void			error(int n);
void			init_vm(t_vm *vm);
void			check_args(int ac, char **av, t_vm *vm);
void			aff_champions(t_vm *vm, int n);
void			aff_memory(t_vm *vm);
void			set_champions_to_memory(t_vm *vm);
int				set_num(t_vm *vm);
int				count_list(t_player *c);
void			and_the_winner_is(t_vm *vm);
void			free_champions(t_player **pl);
void			free_process(t_process **pl);
int				read_op(t_process *current, t_vm *vm);
int				execute_op(t_process *current, t_vm *vm);
void			assign_hexa(unsigned char i, char *str);

int				c_live(t_vm *vm, t_process *current);
int				c_ld(t_vm *vm, t_process *current);
int				c_st(t_vm *vm, t_process *current);
int				c_add(t_vm *vm, t_process *current);
int				c_sub(t_vm *vm, t_process *current);
int				c_and(t_vm *vm, t_process *current);
int				c_or(t_vm *vm, t_process *current);
int				c_xor(t_vm *vm, t_process *current);
int				c_zjmp(t_vm *vm, t_process *current);
int				c_ldi(t_vm *vm, t_process *current);
int				c_sti(t_vm *vm, t_process *current);
int				c_fork(t_vm *vm, t_process *current);
int				c_lld(t_vm *vm, t_process *current);
int				c_lldi(t_vm *vm, t_process *current);
int				c_lfork(t_vm *vm, t_process *current);
int				c_aff(t_vm *vm, t_process *current);
char			read_p_byte(char p_byte, char *tab, char *size, int i);
unsigned char	read_byte(t_vm *vm, t_process *current, int *ic);
int				read_ind(t_vm *vm, t_process *current, int *ic);
int				read_dir(t_vm *vm, t_process *current, int *ic);
int				read_param(char code, t_vm *vm, t_process *current, int *ic);
int				get_addr(int addr);
void			cpy_memory(int i, int size, t_vm *vm, int addr);
void			check_process(t_vm *vm);
void			execute_process(t_vm *vm);

#endif
