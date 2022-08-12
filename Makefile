# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwina <zwina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 16:49:58 by zwina             #+#    #+#              #
#    Updated: 2022/08/07 16:28:15 by zwina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ANSI_RESET			:= \\e[0m
ANSI_BOLD			:= \\e[2m
ANSI_BOLD_RESET		:= \\e[22m
ANSI_ULINE			:= \\e[4m
ANSI_ULINE_RESET	:= \\e[24m
ANSI_ITALIC			:= \\e[3m
ANSI_ITALIC_RESET	:= \\e[23m
ANSI_RED			:= \\e[38;5;1m
ANSI_WHITE			:= \\e[38;5;15m
ANSI_YELLOW			:= \\e[38;5;3m
ANSI_GREEN			:= \\e[38;5;2m
ANSI_ORANGE			:= \\e[38;5;208m
ANSI_GOLD			:= \\e[38;5;214m
ANSI_BLUE			:= \\e[38;5;4m
ANSI_CYAN			:= \\e[38;5;44m

# DIRECTORIES

LIBSDIR		:=	libs
LIBFTDIR	:=	${LIBSDIR}/Libft
SRCSDIR		:=	srcs
OBJSDIR		:=	objs
INCLDIR		:=	includes
GNLDIR		:=	get_next_line
SETUPDIR	:=	setup
SETUPMAPDIR	:=	setup_map
DRAWDIR		:=	draw
HOOKSDIR	:=	hooks


NAME		:=	cub3d
CCWI		:=	cc -Wall -Wextra -Werror -I${INCLDIR} -IPRINT

LIBFTLINK	:=	-L${LIBFTDIR} -lft
LIBFT		:=	${LIBFTDIR}/libft.a
MLXLINK		:=	-lm -lmlx -framework OpenGL -framework AppKit

CGNL		:=		get_next_line.c \
					get_next_line_utils.c
CSETUPMAP	:=			setup_map_grid.c \
						fill_player.c \
						fill_map.c \
						fill_map_utils.c \
						fill_floor_ceiling.c \
						fill_texture.c \
						map_validation.c
CSETUP		:=		$(foreach F,${CSETUPMAP},${SETUPMAPDIR}/${F}) \
					setup_data.c
CDRAW		:=		draw.c \
					draw_line.c
CHOOKS		:=		hooks.c \
					move.c \
					key_look.c
CFILES		:=	$(foreach F,${CGNL},${GNLDIR}/${F}) \
				$(foreach F,${CSETUP},${SETUPDIR}/${F}) \
				$(foreach F,${CDRAW},${DRAWDIR}/${F}) \
				$(foreach F,${CHOOKS},${HOOKSDIR}/${F}) \
				PRINT/print.c \
				my_mlx_pixel_put.c \
				main.c

SRCS		:=	$(foreach F,${CFILES},${SRCSDIR}/${F})
OBJS		:=	$(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))

all : ${NAME}

debug : CCWI += -fsanitize=address -g
debug : all

${NAME} : ${LIBFT} ${OBJSDIR} ${OBJS}
	${CCWI} ${LIBFTLINK} ${MLXLINK} ${OBJS} -o ${NAME}

${OBJS} : ${OBJSDIR}/%.o : ${SRCSDIR}/%.c
	${CCWI} -c $< -o $@

${LIBFT} :
	make all bonus -C ${LIBFTDIR}

${OBJSDIR} :
	mkdir ${OBJSDIR}
	mkdir ${OBJSDIR}/${GNLDIR}
	mkdir ${OBJSDIR}/${SETUPDIR}
	mkdir ${OBJSDIR}/${SETUPDIR}/${SETUPMAPDIR}
	mkdir ${OBJSDIR}/${DRAWDIR}
	mkdir ${OBJSDIR}/${HOOKSDIR}
	mkdir ${OBJSDIR}/PRINT

clean :
	make clean -C ${LIBFTDIR}
	rm -rf ${OBJSDIR}

fclean : clean
	make fclean -C ${LIBFTDIR}

re : fclean all