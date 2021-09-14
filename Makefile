NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

INCLUDES = -lreadline

SRC = minishell.c signals_pa.c start_parsing_pa.c parsing_pa.c check_syntax_pa.c redir_syntax_errors_pa.c init_nodes_pa.c\
	  get_filepath_pa.c env_variable_pa.c set_env_pa.c free_pa.c allocate_pa.c ambigous_redir_pa.c redirection_pa.c\
	  exec_ex.c redirection_ex.c path_ex.c builtin_ex.c chdir_ex.c pwd_ex.c echo_ex.c env_ex.c\
	  unset_ex.c envp_ex.c heredoc_ex.c

PARSING_SRC = allocate_pa.c signals_pa.c ambigous_redir_pa.c check_syntax_pa.c env_variable_pa.c free_pa.c init_nodes_pa.c\
			parsing_main.c start_parsing_pa.c parsing_pa.c redirection_pa.c redir_syntax_errors_pa.c set_env_pa.c\
			get_filepath_pa.c

FLAGS = -Wall -Wextra -Werror

#################
# USE FLAGS
# LINK HEADERS
#################

OBJECT = $(SRC:.c=.o)

PARSING_OBJ = $(PARSING_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	make bonus -sC libft/
	ar rcs $(LIBNAME) $(OBJECT)
	gcc $(LIBNAME) $(LIBFT) $(INCLUDES) -o ../test/$(NAME)

parsing: $(PARSING_OBJ)
	make bonus -sC libft/
	gcc $(PARSING_OBJ) $(LIBFT) $(INCLUDES) -o parsing_mini

%.o:%.c
	gcc -c $<

clean:
	make -sC libft/ clean
	/bin/rm -f $(OBJECT)

fclean: clean
	make -sC libft/ fclean
	/bin/rm -f $(LIBNAME)
	/bin/rm -f parsing_mini
	/bin/rm -f parsing_main.o
	/bin/rm -f ../test/$(NAME)
	/bin/rm -rf parsing_mini.dSYM/

re: fclean all
