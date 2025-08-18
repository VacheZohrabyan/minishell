NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

SRCDIR  := src
OBJDIR  := obj
INCDIR  := inc
LIBFT   := libft

SRC     := \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/init_env.c \
	$(SRCDIR)/free/env_node_free.c \
	$(SRCDIR)/free/split_free.c \
	$(SRCDIR)/free/token_node_free.c \
	$(SRCDIR)/my_signal/sig.c \
	$(SRCDIR)/lexical/lexical.c \
	$(SRCDIR)/lexical/lexical_util.c \
	$(SRCDIR)/lexical/hendle_token.c \
	$(SRCDIR)/parsing/syntax_checker.c \
	$(SRCDIR)/parsing/syntax_checker_utils.c \
	$(SRCDIR)/syntax/syntax.c \
	$(SRCDIR)/builtin/builtin.c \
	$(SRCDIR)/builtin/cmd_pwd.c \
	$(SRCDIR)/builtin/cmd_exit.c \
	$(LIBFT)/split.c \
	$(LIBFT)/is_digit.c \
	$(LIBFT)/substr.c \
	$(LIBFT)/strdup.c \
	$(LIBFT)/strlen.c \
	$(LIBFT)/strcmp.c \
	$(LIBFT)/strjoin.c \
	$(LIBFT)/ft_putstr_fd.c \
	$(LIBFT)/ft_putendl_fd.c \

OBJ     := $(SRC:%.c=$(OBJDIR)/%.o)

HEADERS := $(INCDIR)/libft.h \
		   $(INCDIR)/parser.h \
		   $(INCDIR)/lexical.h \
		   $(INCDIR)/my_signal.h \
		   $(INCDIR)/include.h \
		   $(INCDIR)/syntax.h \
		   $(INCDIR)/builtin.h \

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
