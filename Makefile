NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

INCLUDES = -lreadline

SRC = allocate_pa.c \
	ambigous_redir_pa.c \
	builtin_ex.c \
	chdir_ex.c \
	check_syntax_pa.c \
	echo_ex.c \
	env_ex.c \
	env_variable_pa.c \
	envp_ex.c \
	exec_ex.c \
	extra_args_pa.c \
	free_pa.c \
	get_filepath_pa.c \
	heredoc_ex.c \
	init_nodes_pa.c \
	minishell.c \
	parsing_pa.c \
	path_ex.c \
	pwd_ex.c \
	redir_syntax_errors_pa.c \
	redirection_ex.c \
	redirection_pa.c \
	set_env_pa.c \
	signals_pa.c \
	start_parsing_pa.c \
	unset_ex.c \

PARSING_SRC = allocate_pa.c \
	ambigous_redir_pa.c \
	check_syntax_pa.c \
	env_variable_pa.c \
	extra_args_pa.c \
	free_pa.c \
	get_filepath_pa.c \
	init_nodes_pa.c \
	parsing_main.c \
	parsing_pa.c \
	redir_syntax_errors_pa.c \
	redirection_pa.c \
	set_env_pa.c \
	signals_pa.c \
	start_parsing_pa.c \

FLAGS = -Wall -Wextra -Werror

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

#################
# USE FLAGS
# LINK HEADERS
#################

OBJECT = $(SRC:.c=.o)

PARSING_OBJ = $(PARSING_SRC:.c=.o)

all: credit $(NAME)

$(NAME): $(OBJECT)
	@echo "\n$(YELLOW)█████████████████████████████████████████████████ libft █████████████████████████████████████████████████$(RESET)"
	@make bonus -C libft/
	@ar rcs $(LIBNAME) $(OBJECT)
	@gcc $(LIBNAME) $(LIBFT) $(INCLUDES) -o ../test/$(NAME)
	@echo "\n$(GREEN)████████████████████████████████████████████ Done compiling █████████████████████████████████████████████$(RESET)"

parsing: $(PARSING_OBJ)
	make bonus -sC libft/
	gcc $(PARSING_OBJ) $(LIBFT) $(INCLUDES) -o parsing_mini

%.o:%.c
	gcc -c $<

clean:
	@echo "$(RED)Deleting object files...$(RESET) "
	@make -sC libft/ clean
	@/bin/rm -f $(OBJECT)

fclean: clean
	@echo "$(RED)Deleting libraries, and executables...$(RESET) "
	@make -sC libft/ fclean
	@/bin/rm -f $(LIBNAME)
	@/bin/rm -f ../test/$(NAME)

re: fclean all

credit:
	@echo "$(GREEN)"
	@echo "█████████████████████████████████████████████████████████████████████████████████████████████████████████"
	@echo "█												      	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀	█"
	@echo "█									⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠀	█"
	@echo "█									⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀	█"
	@echo "█   ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░	⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀	█"
	@echo "█   ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░	⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀	█"
	@echo "█   ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░	⠀⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧⠀⠀	█"
	@echo "█   ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░	⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀	█"
	@echo "█   ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗	⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀	█"
	@echo "█   ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝	⠀⢿⣿⡆⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀	█"
	@echo "█   	⠀								 ⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀	█"
	@echo "█									⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀	█"
	@echo "█									⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀	█"
	@echo "█												      	█"
	@echo "█████████████████████████████████████████████████████████████████████████████████████████████████████████"
	@echo "$(RESET)"
	@echo "\n$(BLUE)███████████████████████████████████████████████ minishell ███████████████████████████████████████████████$(RESET)"
