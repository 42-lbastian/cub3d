NAME = cub3D

SRCS = srcs/cub3d.c srcs/error.c srcs/error_2.c srcs/parse_main_map.c srcs/parse_map_utils.c srcs/parse_news_fc_r.c srcs/tools.c srcs/init_screen.c
OBJS = ${SRCS:.c=.o}

CC = clang

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all:	$(NAME)

$(NAME): ${OBJS}
	$(MAKE) -C minilibx-linux
	cp minilibx-linux/libmlx.a .
	$(CC) -o $(NAME) $(CFLAGS) ${OBJS} libmlx.a	-lm -lbsd -lX11 -lXext

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean:	clean
		${RM} ${NAME} libmlx.a
		$(MAKE) clean -C minilibx-linux

re:		fclean all

.PHONY:	all clean fclean re bonus
