NAME = minishell


LIB_DIR = ./libftplus/
LIB = libftplus.a
LIB_P = $(addprefix $(LIB_DIR), $(LIB))

SRCS = main.c \
		parse.c \
		cmd_split.c \
		exit_funcs.c \
		variables.c \
		check_input.c \
		fill_list.c \
		nodes.c

OBJS = $(SRCS:.c=.o)


CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I. -I$(LIB_DIR)
RLFLAGS = -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory


.PHONY: all clean fclean re

all: $(NAME)

$(LIB_P):
	make -C $(LIB_DIR)
	cp $(LIB_DIR)$(LIB) .

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(LIB_P)
	$(CC) $(OBJS) $(LIB_P) -L$(LIB_DIR) -lftplus $(RLFLAGS) -o $(NAME)

clean:
	make fclean -C $(LIB_DIR)
	$(RM) $(OBJS) $(LIB)

fclean: clean 
	$(RM) $(NAME)

re: fclean all	