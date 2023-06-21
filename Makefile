NAME = minishell

IFLAGS = -Iinclude -I$(LIBFT_DIR) -I$(shell brew --prefix readline)/include
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS = -Wall -g -fsanitize=address
LFLAGS = -Llibft -lft -lreadline -lhistory -L$(shell brew --prefix readline)/lib

SRC_DIR = sources
SRCS = b_cd.c expander_variable_length.c \
b_echo.c heredoc.c b_env.c heredoc_expansion.c \
b_exit.c index_in_env.c b_export.c lexer.c \
b_export_utils.c lexer_count_tokens.c \
b_pwd.c lexer_create_tokens.c b_unset.c lexer_utils.c \
builtin_utils.c main.c check_for_builtin.c main_utils.c \
command_utils.c mainprogram.c create_env.c \
debug_printing.c parser.c executer.c \
parser_create_command.c executer_commands.c \
parser_free_commands.c executer_pipes.c \
parser_syntax_validation.c executer_redirections.c \
signal_setters.c executer_utils.c signal_utils.c \
expander.c single_builtin.c expander_build_str.c \
update_oldpwd_env.c expander_length.c update_pwd_env.c \
expander_variable.c update_shlvl.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT_DIR = libft
LIBFTNAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@

$(LIBFT_DIR)/$(LIBFTNAME):
	@$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# testing
TEST_SRCS = test.c
FUNCTION_SRCS = b_cd.c expander_variable_length.c \
		b_echo.c heredoc.c b_env.c heredoc_expansion.c \
		b_exit.c index_in_env.c b_export.c lexer.c \
		b_export_utils.c lexer_count_tokens.c \
		b_pwd.c lexer_create_tokens.c b_unset.c lexer_utils.c \
		builtin_utils.c check_for_builtin.c main_utils.c \
		command_utils.c mainprogram.c create_env.c \
		debug_printing.c parser.c executer.c \
		parser_create_command.c executer_commands.c \
		parser_free_commands.c executer_pipes.c \
		parser_syntax_validation.c executer_redirections.c \
		signal_setters.c executer_utils.c signal_utils.c \
		expander.c single_builtin.c expander_build_str.c \
		update_oldpwd_env.c expander_length.c update_pwd_env.c \
		expander_variable.c update_shlvl.c

TEST_FLAGS = -Wall -g $(IFLAGS) $(LFLAGS)
test: $(NAME)
	@$(CC) $(TEST_FLAGS) $(addprefix tests/, $(TEST_SRCS)) $(addprefix sources/, $(FUNCTION_SRCS)) $(LIBFT_DIR)/$(LIBFTNAME) -o test.out
	@./test.out
	@rm -rf test.out*
