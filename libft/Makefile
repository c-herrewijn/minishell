# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cherrewi <cherrewi@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/19 15:14:28 by cherrewi      #+#    #+#                  #
#    Updated: 2023/05/11 13:42:33 by cherrewi      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_printf.c ft_printf_utils.c ft_isspace.c ft_isinteger.c \
		ft_printf_fd.c ft_printf_utils_fd.c ft_abs.c ft_min_max.c \
		ft_get_next_line.c
SRCS_BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c
OBJS_REG = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
FLAGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
OBJS = $(OBJS_REG) $(OBJS_BONUS)
else
OBJS = $(OBJS_REG)
endif

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

%.o: %.c
	@$(CC) -c $(FLAGS) $< -o $@

clean:
	@rm -f $(OBJS_REG) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJS_BONUS) $(OBJS_REG)
	@$(MAKE) WITH_BONUS=1

.PHONY: all clean fclean re bonus
