NAME    := minishell
CC      := cc
CFLAGS  := -g3 -Wall -Wextra -Werror #-fsanitize=address

SRCDIR  := src
OBJDIR  := obj
INCDIR  := inc
LIBFT   := libft

SRC     := \
	$(SRCDIR)/main.c \
	$(SRCDIR)/main_utils.c \
	$(SRCDIR)/parsing/parsing.c \
	$(SRCDIR)/parsing/parsing_utils.c \
	$(SRCDIR)/parsing/parsing_utils2.c \
	$(SRCDIR)/parsing/env_utils.c \
	$(SRCDIR)/parsing/init_env.c \
	$(SRCDIR)/free/split_free.c \
	$(SRCDIR)/free/token_node_free.c \
	$(SRCDIR)/free/free_command.c \
	$(SRCDIR)/free/free_shell.c \
	$(SRCDIR)/free/free_split.c \
	$(SRCDIR)/my_signal/sig1.c \
	$(SRCDIR)/my_signal/sig2.c \
	$(SRCDIR)/lexical/lexical.c \
	$(SRCDIR)/lexical/my_split.c \
	$(SRCDIR)/lexical/my_split_utils2.c \
	$(SRCDIR)/lexical/my_split_utils1.c \
	$(SRCDIR)/lexical/lexical_util.c \
	$(SRCDIR)/lexical/hendle_token.c \
	$(SRCDIR)/parsing/syntax_checker.c \
	$(SRCDIR)/parsing/syntax_checker_utils.c \
	$(SRCDIR)/builtin/builtin.c \
	$(SRCDIR)/builtin/cmd_pwd.c \
	$(SRCDIR)/builtin/cmd_exit.c \
	$(SRCDIR)/builtin/cmd_env.c \
	$(SRCDIR)/builtin/cmd_history.c \
	$(SRCDIR)/builtin/history_utils.c \
	$(SRCDIR)/builtin/cmd_cd.c \
	$(SRCDIR)/builtin/cmd_echo.c \
	$(SRCDIR)/builtin/cmd_export.c \
	$(SRCDIR)/builtin/export_utils.c \
	$(SRCDIR)/builtin/cmd_unset.c \
	$(SRCDIR)/chgitem_inch_dnem/gnacinq.c \
	$(SRCDIR)/chgitem_inch_dnem/gnacinq_utils.c \
	$(SRCDIR)/chgitem_inch_dnem/any.c \
	$(SRCDIR)/chgitem_inch_dnem/path.c \
	$(SRCDIR)/chgitem_inch_dnem/heredoc.c \
	$(SRCDIR)/chgitem_inch_dnem/command_proc.c \
	$(SRCDIR)/chgitem_inch_dnem/command_many_proc.c \
	$(SRCDIR)/chgitem_inch_dnem/command_many_proc_utils.c \
	$(SRCDIR)/run.c \

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
