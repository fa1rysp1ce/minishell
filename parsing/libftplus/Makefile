# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junruh <junruh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 12:57:47 by junruh            #+#    #+#              #
#    Updated: 2024/09/10 17:41:53 by junruh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftplus.a

#directories

SRC_DIR = srcs
HDR_DIR = includes
OBJ_DIR = objs
LIBFT_DIR = libft
GNL_DIR = get_next_line

#source files and their paths

SRC_FLS = $(LIBFT_FLS)\
		  $(GNL_FLS)

LIBFT_FLS = $(addprefix $(SRC_DIR)/,\
				$(LIBFT_DIR)/ft_atoi.c\
				$(LIBFT_DIR)/ft_atol.c\
				$(LIBFT_DIR)/ft_bzero.c\
				$(LIBFT_DIR)/ft_calloc.c\
				$(LIBFT_DIR)/ft_isalnum.c\
				$(LIBFT_DIR)/ft_isalpha.c\
				$(LIBFT_DIR)/ft_isascii.c\
				$(LIBFT_DIR)/ft_isdigit.c\
				$(LIBFT_DIR)/ft_isprint.c\
				$(LIBFT_DIR)/ft_itoa.c\
				$(LIBFT_DIR)/ft_memchr.c\
				$(LIBFT_DIR)/ft_memcmp.c\
				$(LIBFT_DIR)/ft_memcpy.c\
				$(LIBFT_DIR)/ft_memmove.c\
				$(LIBFT_DIR)/ft_memset.c\
				$(LIBFT_DIR)/ft_split.c\
				$(LIBFT_DIR)/ft_strchr.c\
				$(LIBFT_DIR)/ft_strdup.c\
				$(LIBFT_DIR)/ft_striteri.c\
				$(LIBFT_DIR)/ft_strjoin.c\
				$(LIBFT_DIR)/ft_strlcat.c\
				$(LIBFT_DIR)/ft_strlcpy.c\
				$(LIBFT_DIR)/ft_strlen.c\
				$(LIBFT_DIR)/ft_strmapi.c\
				$(LIBFT_DIR)/ft_strncmp.c\
				$(LIBFT_DIR)/ft_strnstr.c\
				$(LIBFT_DIR)/ft_strrchr.c\
				$(LIBFT_DIR)/ft_strtrim.c\
				$(LIBFT_DIR)/ft_substr.c\
				$(LIBFT_DIR)/ft_tolower.c\
				$(LIBFT_DIR)/ft_toupper.c)

GNL_FLS = $(addprefix $(SRC_DIR)/,\
			$(GNL_DIR)/get_next_line.c\
			$(GNL_DIR)/get_next_line_utils.c)

#add filepaths

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FLS))
DEPS = $(OBJS:.o=.d)

#flags

CC = cc
RM = rm -rf
CFLGS = -Wall -Werror -Wextra
IFLGS = -I $(HDR_DIR)
DFLGS = -MMD -MP -O1

#rules

.PHONY: all clean fclean re

all: $(NAME)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(LIBFT_DIR)
	mkdir -p $(OBJ_DIR)/$(GNL_DIR)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
