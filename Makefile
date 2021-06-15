NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

SRC = minishell.c parsing.c struct_setup.c

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
	make -sC libft/ clean
	/bin/rm -f $(OBJECT)

fclean: clean
	make -sC libft/ fclean
	/bin/rm -f $(LIBNAME)
	/bin/rm -f $(NAME)

re: fclean all