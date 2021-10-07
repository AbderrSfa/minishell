NAME = minishell

LIBNAME = minishell.a

LIBFT = libft/libft.a

INCLUDES = -lreadline

SRC =	builtin_ex.c \
	chdir_ex.c \
	envp_ex.c \
	exec_ex.c \
	path_ex.c \
	pwd_ex.c \
	unset_ex.c \
	heredoc_ex.c \
	cmd_ex.c \
	allocate_pa.c \
	ambigous_redir_pa.c \
	check_syntax_pa.c \
	env_variable_pa.c \
	extra_args_pa.c \
	free_pa.c \
	get_filepath_pa.c \
	init_nodes_pa.c \
	minishell.c \
	parsing_pa.c \
	redir_syntax_errors_pa.c \
	redirection_ex.c \
	redirection_pa.c \
	set_env_pa.c \
	start_parsing_pa.c \

FLAGS = -Wall -Wextra -Werror
LDFLAGS="-L$(HOME)/.brew/opt/readline/lib"
CPPFLAGS="-I$(HOME)/.brew/opt/readline/include"

HEADERFILES = parsing.h exec.h libft/libft.h

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

OBJECT = $(SRC:.c=.o)

all: credit $(NAME)

$(NAME): $(OBJECT)
	@echo "$(BLUE)█████████████████████████████████████████████████████████████████████████████████████████████████████████$(RESET)"
	@echo "\n$(YELLOW)█████████████████████████████████████████████████ libft █████████████████████████████████████████████████$(RESET)"
	@make bonus -C libft/
	@ar rcs $(LIBNAME) $(OBJECT)
	@mkdir -p ./output
	@gcc $(LIBNAME) $(LIBFT) $(INCLUDES) $(LDFLAGS) -o ./output/$(NAME)
	@echo "\n$(GREEN)██████████████████████████████ Done compiling (minishell in output folder) ██████████████████████████████$(RESET)"

%.o:%.c $(HEADERFILES)
	@echo "$(BLUE)█$(RESET) compiling $< ... \r\t\t\t\t\t\t\t\t\t\t\t\t\t$(BLUE)█$(RESET)"
	@gcc -c $< $(CPPFLAGS) $(FLAGS)

clean:
	@echo "$(RED)Deleting:$(RESET) object files..."
	@make -sC libft/ clean
	@/bin/rm -f $(OBJECT)

fclean: clean
	@echo "$(RED)Deleting:$(RESET) $(LIBFT)..."
	@make -sC libft/ fclean
	@echo "$(RED)Deleting:$(RESET) $(LIBNAME)..."
	@/bin/rm -f $(LIBNAME)
	@echo "$(RED)Deleting:$(RESET) $(NAME)..."
	@/bin/rm -rf ./output

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
	@echo "$(BLUE)███████████████████████████████████████████████ minishell ███████████████████████████████████████████████$(RESET)"
