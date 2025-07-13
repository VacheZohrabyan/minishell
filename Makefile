NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

SRCDIR  := src
OBJDIR  := obj
INCDIR  := inc
LIBFT   := libft

SRC     := \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parsing/init_env.c \
	$(SRCDIR)/parsing/init_token \
	$(SRCDIR)/free/free_init_env.c \
	$(LIBFT)/split.c \
	$(LIBFT)/substr.c \
	$(LIBFT)/strdup.c \
	$(LIBFT)/strlen.c \
	$(LIBFT)/strtrim.c \

OBJ     := $(SRC:%.c=$(OBJDIR)/%.o)

HEADERS := $(INCDIR)/minishell.h \
		   $(INCDIR)/libft.h \
		   $(INCDIR)/parser.h

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
