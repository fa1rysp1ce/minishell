# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 15:27:39 by inbar             #+#    #+#              #
#    Updated: 2024/12/13 12:44:13 by ilazar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# to supress unavoidable readline leaks:
# valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

LIB_DIR = ./libftplus
LIB = libftplus.a
LIB_PATH = $(addprefix $(LIB_DIR)/,$(LIB))

LIB_LINK = -L$(LIB_DIR)


MAIN_SRCS = main.c errors.c clean_free.c

PARSING_SRCS =  exit_funcs.c variables.c nodes.c parse.c \
		cmd_split.c check_input.c fill_list.c helpers.c
		
EXECUTION_SRCS = init_shell.c execute.c exec_paths.c \
		redirection.c redirection_utils.c heredoc.c heredoc_utils.c \
		pipeline.c pipeline_utils.c signals.c signals_utils.c exit_status.c
		

EXEC_BUILTINS = utils.c builtins.c cd_utils.c exit.c export.c unset.c


SRCS = 	$(addprefix srcs/, $(MAIN_SRCS)) \
		$(addprefix srcs/parsing/, $(PARSING_SRCS)) \
       	$(addprefix srcs/execution/, $(EXECUTION_SRCS)) \
		$(addprefix srcs/execution/builtins/, $(EXEC_BUILTINS))
       
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

INCLUDE_DIR = includes
LIB_INC_DIR = $(LIB_DIR)/includes/

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(INCLUDE_DIR) -I$(LIB_INC_DIR)
RLFLAGS = -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline -lhistory


.PHONY: all clean fclean re

all: $(NAME)

$(LIB_PATH):
	make -C $(LIB_DIR)
	cp $(LIB_PATH) .
	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: srcs/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<
	
$(OBJ_DIR)/%.o: srcs/parsing/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: srcs/execution/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: srcs/execution/builtins/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<


$(NAME):  $(LIB_PATH) $(OBJS)
	$(CC) $(OBJS) $(LIB_PATH) $(LIB_LINK) $(RLFLAGS) -lftplus -o $(NAME)

clean:
	make fclean -C $(LIB_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) $(LIB)

fclean: clean 
	$(RM) $(NAME)

re: fclean all	
