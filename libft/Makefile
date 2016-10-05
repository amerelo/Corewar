# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 21:08:02 by flevesqu          #+#    #+#              #
#    Updated: 2016/05/09 17:30:08 by jblondea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDES = ./includes/
SRC = ft_atoi.c\
	  ft_bzero.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_itoa.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_lstadd.c\
	  ft_lstpushback.c\
	  ft_lstdel.c\
	  ft_lstdelone.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstnew.c\
	  ft_lstlast.c\
	  ft_lstgetn.c\
	  ft_lstswap.c\
	  ft_lstlast.c\
	  ft_lstgetn.c\
	  ft_strndup.c\
	  ft_lstaddn.c\
	  get_next_line.c\
	  ft_printf.c\
	  ft_strchar.c\
	  ft_strscat.c\
	  ft_printf/conv_char.c\
	  ft_printf/conv_nb1.c\
	  ft_printf/conv_nb2.c\
	  ft_printf/conv_str.c\
	  ft_printf/conversion.c\
	  ft_printf/flags.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDES)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
