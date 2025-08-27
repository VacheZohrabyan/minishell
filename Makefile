NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror #-fsanitize=address

SRCDIR  := src
OBJDIR  := obj
INCDIR  := inc
LIBFT   := libft

SRC     := \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/parsing_utils.c \
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
	$(SRCDIR)/builtin/builtin.c \
	$(SRCDIR)/builtin/cmd_pwd.c \
	$(SRCDIR)/builtin/cmd_exit.c \

OBJ     := $(SRC:%.c=$(OBJDIR)/%.o)

HEADERS := $(INCDIR)/parser.h \
		   $(INCDIR)/lexical.h \
		   $(INCDIR)/my_signal.h \
		   $(INCDIR)/include.h \
		   $(INCDIR)/syntax.h \
		   $(INCDIR)/builtin.h \
		   $(INCDIR)/types.h \

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: lib $(NAME)

$(NAME): $(OBJ)  $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME) -L./$(LIBFT) -lft

lib:
	make -C $(LIBFT)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
