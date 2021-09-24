# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 16:36:22 by asfaihi           #+#    #+#              #
#    Updated: 2021/09/24 15:15:00 by asfaihi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c \
	  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putstr.c ft_putchar.c \
	  ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	  ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	  ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRC_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c \
		ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJECT = $(SRC:%.c=%.o)

OBJECT_BONUS = $(SRC_BONUS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJECT)
	@ar rc $(NAME) $(OBJECT)

bonus: $(NAME) $(OBJECT_BONUS)
	@echo "$(YELLOW)█████████████████████████████████████████████████████████████████████████████████████████████████████████$(RESET)"
	@ar rc $(NAME) $(OBJECT_BONUS)

%.o:%.c libft.h
	@echo "$(YELLOW)█$(RESET) compiling $< ... \r\t\t\t\t\t\t\t\t\t\t\t\t\t$(YELLOW)█$(RESET)"
	@gcc $(FLAGS) -c $<

clean:
	/bin/rm -f $(OBJECT) $(OBJECT_BONUS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
