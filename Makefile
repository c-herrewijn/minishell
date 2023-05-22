NAME = minishell
# CFLAGS = -Wall -Werror -Wextra -lreadline
CFLAGS = -Wall -lreadline -g
SRC_DIR = sources
SRCS =	builtin_unset.c check_for_builtin.c create_env.c debug_printing.c \
		builtin_utils.c echo_cd_pwd.c export_env_exit.c lexer_count_tokens.c \
		lexer_create_tokens.c lexer_utils.c lexer.c main.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT_DIR = libft
LIBFTNAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

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
FUNCTION_SRCS = builtins.c lexer_count_tokens.c lexer_utils.c lexer.c

test: $(NAME)
	@$(CC) -g $(FLAGS) $(addprefix tests/, $(TEST_SRCS)) $(addprefix sources/, $(FUNCTION_SRCS)) $(LIBFT_DIR)/$(LIBFTNAME) -o test.out
	@./test.out
	@rm -rf test.out*
