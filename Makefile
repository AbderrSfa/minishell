# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 12:07:32 by asfaihi           #+#    #+#              #
#    Updated: 2021/07/06 15:07:39 by asfaihi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

SRC = minishell_pa.c parsing_pa.c init_nodes_pa.c env_variable_pa.c set_env_pa.c free_pa.c allocate_pa.c redirection_pa.c

INCLUDES = -lreadline

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	make bonus -C libft/
	ar rcs $(LIBNAME) $(OBJECT)
	gcc $(LIBNAME) $(LIBFT) $(INCLUDES) -o $(NAME) -g

%.o:%.c
	gcc -c $<

clean:
	make -C libft/ clean
	/bin/rm -f $(OBJECT)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(LIBNAME)
	/bin/rm -f $(NAME)
	/bin/rm -rf a.out.dSYM/

re: fclean all