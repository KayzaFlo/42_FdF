# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 11:55:10 by fgeslin           #+#    #+#              #
#    Updated: 2022/12/19 13:04:58 by fgeslin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####	CONFIG		############################################################
NAME		:= fdf
LIBFT		:= libft/libft.a
CC			:= gcc
AR			:= ar -rcs
RM			:= rm -f
CFLAGS		= -Wall -Wextra -Werror

#####	SOURCES		############################################################
SRC			=	src/fdf.c \
				src/input.c \
				src/draw_basics.c \
				src/draw_iso.c \
				src/alloc.c \
				src/parsing.c
SRC_BONUS	=	src_bonus/fdf.c \
				src_bonus/input.c \
				src_bonus/draw_basics.c \
				src_bonus/draw_iso.c \
				src_bonus/tween.c \
				src_bonus/alloc.c \
				src_bonus/parsing.c \
				src_bonus/update.c \
				src_bonus/utils.c
OBJ			= $(SRC:.c=.o)
OBJ_BONUS	= $(SRC_BONUS:.c=.o)

#####	Makefile  objs		###################################################
WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
PINK		:= \033[1;35m
CYAN 		:= \033[1;36m

.c.o:
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}$(NAME) ${WHITE}..."
	@ $(CC) -o $(NAME) $(OBJ) $(LIBFT) -lmlx -framework OpenGL -framework AppKit
	@ echo "$(CYAN)$(NAME) $(GREEN)created$(WHITE) ✔️"

$(LIBFT):
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}${LIBFT} ${WHITE}..."
	@ $(MAKE) -C libft/
	@ echo "$(CYAN)$(LIBFT) $(GREEN)created$(WHITE) ✔️"

bonus: $(LIBFT) $(OBJ_BONUS)
	@ echo "$(GREEN)Compilation ${WHITE}of ${CYAN}$(NAME) ${WHITE}..."
	@ $(CC) -o $(NAME) $(OBJ_BONUS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit
	@ echo "$(CYAN)$(NAME) $(GREEN)created$(WHITE) ✔️"

clean:
	@ ${RM} $(OBJ) $(OBJ_BONUS)
	@ $(MAKE) clean -C libft/
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE)and $(CYAN)$(LIBFT) $(WHITE)objs ✔️"

fclean: clean
	@ ${RM} $(NAME)
	@ $(MAKE) fclean -C libft/
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(WHITE)and $(CYAN)$(LIBFT) $(WHITE)binary ✔️"

re: fclean all

.PHONY:		all clean fclean re
