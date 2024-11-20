NAME	= libft.a

# directories
#SRCDIR	= ./srcs
INCDIR	= .
OBJDIR	= ./obj

# src / obj files
SRC		= ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_putstr_fd.c ft_putchar_fd.c \
			ft_strdup.c ft_strchr.c ft_strcmp.c ft_memset.c

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= cc
CFLAGS	= -Wall -Wextra -Werror


# ft libraries
#FT_LIB	= $(addprefix $(FT)/,libraries.a)
#FT_INC	= -I ./libraries/includes
#FT_LNK	= -L ./libraries/includes

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

#$(OBJDIR)/%.o:$(SRCDIR)/%.c
#	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<
$(OBJDIR)/%.o:%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<


$(NAME): obj $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	
clean:
	rm -rf $(OBJDIR)
	#make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	#make -C $(FT) fclean

re: fclean all

.PHONY: all bonus clean fclean re
