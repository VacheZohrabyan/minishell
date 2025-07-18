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
	$(SRCDIR)/parsing/syntax_checker.c \
	$(LIBFT)/split.c \
	$(LIBFT)/substr.c \
	$(LIBFT)/strdup.c \
	$(LIBFT)/strlen.c \

OBJ     := $(SRC:%.c=$(OBJDIR)/%.o)

HEADERS := $(INCDIR)/libft.h \
		   $(INCDIR)/parser.h \
		   $(INCDIR)/lexical.h \
		   $(INCDIR)/my_signal.h \

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
