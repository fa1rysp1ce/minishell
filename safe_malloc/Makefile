NAME = lib_malloc.a
SRCS = safe_malloc.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
