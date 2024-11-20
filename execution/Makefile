NAME	= minishell

# directories
SRCDIR	= ./src
INCDIR	= .
OBJDIR	= ./obj

# src / obj files
SRC		=	main.c clean_free.c init_shell.c debug.c execute.c errors.c redirection_utils.c
SRC		+=	redirection.c heredoc.c builtin_utils.c builtins_misc.c builtins_cd.c
SRC		+=	pipeline.c pipeline_utils.c exec_paths.c
SRC		+=	jake_nodes.c

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= cc
CFLAGS	= -Wall -Wextra -Werror


# libft
#FT_INC	= -I ./libraries/includes
FT		= ./libft
FT_LIB	= $(addprefix $(FT)/,libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)


$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $< -lreadline

$(FT_LIB):
	@make -C $(FT)

$(NAME): obj $(OBJ)
	$(CC) $(OBJ) $(FT_LNK) $(FT_LIB) -lm -o $(NAME) -lreadline
	
clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all

.PHONY: all bonus clean fclean re
