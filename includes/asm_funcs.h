/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_funcs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:11:16 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/23 16:30:49 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_FUNCS_H
# define ASM_FUNCS_H

/*
** load_ops.c
*/

void		load_ops(t_asm *parsed_champ);

/*
** load_file.c
*/

int			load_file(char *file_name, t_asm *parsed_champ);

/*
** compile_champ.c
*/

int			compile_champ(t_asm *parsed_champ);

/*
** write_champ.c
*/

void		write_champ(t_asm *parsed_champ);

/*
** head.c
*/

int			load_head_instr(char *str, int fd, t_asm *parsed_champ,
								t_head_instr *head_instr);
int			load_head(char *str, int fd, t_asm *parsed_champ);

/*
** head_parts.c
*/

int			check_name(char *str, int fd, t_asm *parsed_champ);
int			check_comment(char *str, int fd, t_asm *parsed_champ);

/*
** label.c
*/

int			load_label(char *str, t_asm *parsed_champ);

/*
** instruction.c
*/

int			load_instr(char *str, t_asm *parsed_champ);

/*
** char_types.c
*/

int			is_empty_char(char c);
int			is_comment_char(char c);
int			is_label_char(char c);

/*
** string_types.c
*/

int			is_empty(char *str);
int			is_comment(char *str);

/*
** error.c
*/

int			ft_error();

/*
** print_ops.c
*/

void		print_op_types(t_asm *parsed_champ);

/*
** print_champ.c
*/

void		print_champ(t_asm *parsed_champ);

/*
** ft_logs.c
*/

int			ft_logs(t_asm *env, const char *format, ...);

/*
** string_tools.c
*/

char		*ft_start_trim(char *str);
int			ft_strisdigit(char *str);
int			ft_append(char *dst, int index, char *src);
int			len_before_empty(char *str);
int			len_before_empty_or_comment(char *str);

/*
** compile_champ.c
*/

int			get_types(t_asm *parsed_champ, t_instruction *element);
int			test_arg(int *x, t_asm *parsed_champ, t_list **element);
int			dis_to_hex(t_asm *parsed_champ, t_instruction *element, int *i,
						int p);
int			find_label(t_asm *champ, t_instruction *element, int p, int *dis);
void		set_num(t_instruction *element, int *i, int p);
void		set_num2(t_instruction *element, int *i, int p);
int			test_in(t_asm *parsed_champ, t_instruction *element);
int			test_param(t_asm *parsed_champ, t_op op, t_instruction *element);
int			find_size(t_op op, t_instruction *element);
t_op		*find_op(t_asm *parsed_champ, int opcode);

#endif
