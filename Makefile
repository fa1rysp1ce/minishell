NAME = minishell


LIB_DIR = ./libftplus
LIB = libftplus.a
LIB_PATH = $(addprefix $(LIB_DIR)/,$(LIB))
MALLOC_DIR = ./safe_malloc
MALLOC = safe_malloc.a
MALLOC_PATH = $(addprefix $(MALLOC_DIR)/,$(MALLOC))

EXTRA_PARH = $(LIB_PATH) $(MALLOC_PATH)
LIB_LINK = -L$(LIB_DIR) -L$(MALLOC_DIR)

PARSING_SRCS = main.c exit_funcs.c variables.c nodes.c parse.c \
		cmd_split.c check_input.c fill_list.c
		
EXECUTION_SRCS = clean_free.c init_shell.c debug.c execute.c errors.c \
		redirection.c redirection_utils.c heredoc.c \
		builtin_utils.c builtins_misc.c builtins_cd.c \
		pipeline.c pipeline_utils.c exec_paths.c jake_nodes.c

SRCS = $(addprefix parsing/, $(PARSING_SRCS)) \
       $(addprefix execution/, $(EXECUTION_SRCS))
       
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

INCLUDE_DIR = includes
LIB_INC_DIR = $(LIB_DIR)/includes/

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(INCLUDE_DIR) -I$(LIB_INC_DIR) -I$(MALLOC_DIR)
RLFLAGS = -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory


.PHONY: all clean fclean re

all: $(NAME)

$(LIB_PATH):
	make -C $(LIB_DIR)
	cp $(LIB_PATH) .
	
$(MALLOC_PATH):
	make -C $(MALLOC_DIR)
	cp $(MALLOC_PATH) .
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: parsing/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: execution/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<


$(NAME):  $(LIB_PATH) $(MALLOC_PATH) $(OBJS)
	$(CC) $(OBJS) $(EXTRA_PARH) $(LIB_LINK) $(RLFLAGS) -lftplus -o $(NAME)

clean:
	make fclean -C $(LIB_DIR)
	make fclean -C $(MALLOC_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) $(LIB) $(MALLOC)

fclean: clean 
	$(RM) $(NAME)

re: fclean all	
