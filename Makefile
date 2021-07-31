NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

SRC = minishell.c parsing_pa.c check_syntax_pa.c redir_syntax_errors_pa.c init_nodes_pa.c\
	  get_filepath_pa.c env_variable_pa.c set_env_pa.c free_pa.c allocate_pa.c redirection_pa.c\
	  exec_ex.c redirection_ex.c path_ex.c builtin_ex.c chdir_ex.c pwd_ex.c echo_ex.c env_ex.c\
	  unset_ex.c

INCLUDES = -lreadline

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	make bonus -sC libft/
	ar rcs $(LIBNAME) $(OBJECT)
	gcc $(LIBNAME) $(LIBFT) $(INCLUDES) -o ../test/$(NAME) -g

%.o:%.c
	gcc -c $<

clean:
	make -sC libft/ clean
	/bin/rm -f $(OBJECT)

fclean: clean
	make -sC libft/ fclean
	/bin/rm -f $(LIBNAME)
	/bin/rm -f $(NAME)
	/bin/rm -rf a.out.dSYM/

re: fclean all
