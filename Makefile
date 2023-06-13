NAME = minishell

IFLAGS = -Iinclude -I$(LIBFT_DIR) -I$(shell brew --prefix readline)/include
CFLAGS = -Wall -g -fsanitize=address
LFLAGS = -Llibft -lft -lreadline -lhistory -L$(shell brew --prefix readline)/lib

SRC_DIR = sources
SRCS = b_cd.c builtin_utils.c lexer_utils.c \
b_echo.c check_for_builtin.c main.c b_export_utils.c \
b_env.c create_env.c update_pwd_env.c update_oldpwd_env.c\
b_exit.c debug_printing.c parser.c \
b_export.c lexer.c parser_create_command.c \
b_pwd.c lexer_count_tokens.c parser_syntax_validation.c \
builtin_unset.c lexer_create_tokens.c parser_free_commands.c \
executer_redirections.c executer.c heredoc.c command_utils.c \
single_builtin.c single_non_builtin.c expander.c extra_main.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT_DIR = libft
LIBFTNAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	$(CC) $(CFLAGS) $(IFLAGS) $^ -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(CFLAGS) $(IFLAGS) $< -o $@

$(LIBFT_DIR)/$(LIBFTNAME):
	@$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# testing
TEST_SRCS = test.c
FUNCTION_SRCS =	builtin_unset.c check_for_builtin.c create_env.c debug_printing.c \
		builtin_utils.c echo_cd_pwd.c export_env_exit.c lexer_count_tokens.c \
		lexer_create_tokens.c lexer_utils.c lexer.c parser.c parser_syntax_validation.c \
		parser_create_command.c

test: $(NAME)
	@$(CC) -g $(FLAGS) $(addprefix tests/, $(TEST_SRCS)) $(addprefix sources/, $(FUNCTION_SRCS)) $(LIBFT_DIR)/$(LIBFTNAME) -o test.out
	@./test.out
	@rm -rf test.out*
