SRCS	= make_the_fractal.c main.c utils1.c utils2-str.c move.c 

OBJS	= ${SRCS:.c=.o}

NAME	= fract-oloz

RM		= rm -f

CC		= gcc

MLX_PATH = minilibx-linux/
MLX_LIB = ${MLX_PATH}/libmlx.a

MLX_FLAGS_DEBIAN = -lmlx -lXext -lX11 -lm
MLX_FLAGS_OLOZ = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm
MLX_FLAGS_OSX = -g -I /usr/X11/include -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit
MLX_DIR = ./mlx
MLX_A = $(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Linux.a

CFLAGS	= -Wall -Wextra -Werror

SRCSO = $(SRCS:.c=.o)

$(NAME): ${SRCSO} mlx_compil
	${CC} ${CFLAGS}  -I. -o ${NAME} ${SRCSO} -L ${MLX_PATH} -lmlx -lXext -lX11 -lm

linux_compil: 
	$(CC) -g -c $(CC_FLAGS) -I. $(SRCS)
	$(CC) -g $(MLX_FLAGS_DEBIAN) $(SRCSO) $(MLX_A) -o $(NAME)

xibao_compil:
	$(CC) -c $(CC_FLAGS) -I. $(SRCS)
	$(CC) $(MLX_FLAGS_XIBAO) $(SRCSO) $(MLX_A) -o $(NAME)

mlx_compil:
	make -C ${MLX_PATH}

clean:
			rm -f $(SRCSO)

all:		${NAME}
			rm -f $(SRCSO)

fclean:		clean
			${RM} ${NAME}

fmlxclean:	fclean
			${RM} libmlx.a
			${RM} libmlx.dylib

re:			fclean all

bonus:		${OBJS_B}
			${CC} -I${INCLS} ${CFLAGS} -o ${NAME} ${OBJS_B}

.PHONY:		all clean fclean re
