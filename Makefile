# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 16:49:58 by zwina             #+#    #+#              #
#    Updated: 2022/08/27 13:38:09 by lelhlami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DIRECTORIES

LIBSDIR			:=	libs
LIBFTDIR		:=	${LIBSDIR}/Libft
SRCSDIR			:=	srcs
OBJSDIR			:=	objs
INCLDIR			:=	includes
GNLDIR			:=	get_next_line
SETUPDIR		:=	setup
SETUPMAPDIR		:=	setup_map
DRAWDIR			:=	draw
DRAWDIR_MINI	:=	draw_minimap
HOOKSDIR		:=	hooks


NAME		:=	cub3d
CCWI		:=	cc -Wall -Wextra -Werror -I${INCLDIR}

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
						fill_floor_ceiling_utils.c \
						fill_texture.c \
						map_validation.c
CSETUP		:=		$(foreach F,${CSETUPMAP},${SETUPMAPDIR}/${F}) \
					setup_data.c
CDRAW_MINI	:=		draw_mini_map.c \
					draw_mini_map_utils.c
CDRAW		:=		$(foreach F,${CDRAW_MINI},${DRAWDIR_MINI}/${F}) \
					draw.c \
					raycasting.c \
					raycast_x.c \
					raycast_y.c \
					draw_ray_x.c \
					draw_ray_y.c \
					draw_line.c
CHOOKS		:=		hooks.c \
					move.c \
					key_look.c
CFILES		:=	$(foreach F,${CGNL},${GNLDIR}/${F}) \
				$(foreach F,${CSETUP},${SETUPDIR}/${F}) \
				$(foreach F,${CDRAW},${DRAWDIR}/${F}) \
				$(foreach F,${CHOOKS},${HOOKSDIR}/${F}) \
				my_mlx_pixel_put.c \
				print/print.c \
				main.c

SRCS		:=	$(foreach F,${CFILES},${SRCSDIR}/${F})
OBJS		:=	$(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))

all : ${NAME}

debug : CCWI += -fsanitize=address -g
debug : all

bonus : all

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
	mkdir ${OBJSDIR}/${DRAWDIR}/${DRAWDIR_MINI}
	mkdir ${OBJSDIR}/${HOOKSDIR}
	mkdir ${OBJSDIR}/print

clean :
	make clean -C ${LIBFTDIR}
	rm -rf ${OBJSDIR}

fclean : clean
	make fclean -C ${LIBFTDIR}
	rm -rf ${NAME}

re : fclean all