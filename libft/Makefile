# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 20:06:49 by fbraune           #+#    #+#              #
#    Updated: 2025/07/20 19:33:17 by fbraune          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a
CC   		= cc
Flag 		= -Wall -Wextra -Werror -c
SRC  		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_strcmp.c\
                ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
                ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
                ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
                ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
                ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c ft_atoli.c ft_sqrt.c ft_issign.c \
                get_next_line_bonus.c ft_count_words.c ft_free_split.c ft_atoi_base.c ft_arr_len.c
BONUS		= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
                ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJ  		= $(SRC:.c=.o)
BONUS_OBJ	= $(BONUS:.c=.o)
RM  		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(OBJ): libft.h
	$(CC) $(Flag) $(SRC)

bonus: $(OBJ) $(BONUS_OBJ) $(FT_PRINTF_LIB)
	ar -rcs $(NAME) $(OBJ) $(BONUS_OBJ) $(FT_PRINTF_LIB)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
