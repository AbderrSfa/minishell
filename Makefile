NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

SRC = minishell.c parsing.c

INCLUDES = -lreadline

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	make -sC libft/
	ar rcs $(LIBNAME) $(OBJECT)
	gcc $(LIBNAME) $(LIBFT) $(INCLUDES) -o $(NAME)

%.o:%.c
	gcc -c $<

clean:
	/bin/rm -f $(OBJECT)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all