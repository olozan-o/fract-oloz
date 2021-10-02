SRCS	= make_the_fractal.c main.c utils1.c utils2-str.c move.c 

OBJS	= ${SRCS:.c=.o}

NAME	= fract-oloz

RM		= rm -f

CC		= gcc

INCLS	= -I. -Iminilibx_mms -Iminilibx_opengl

LIBMLX 	= libmlx.dylib \
		libmlx.a

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCLS}
			@echo "Compiled "$<" successfully!"


${NAME}:	${OBJS}
			@make -C ./minilibx_opengl
			@make -C ./minilibx_mms
			@cp ./minilibx_opengl/libmlx.a libmlx.a
			@cp ./minilibx_mms/libmlx.dylib libmlx.dylib
			${CC} ${INCLS} ${CFLAGS} $(LIBMLX) -o ${NAME} ${OBJS} 
		
clean:
			${RM} ${OBJS}

all:		${NAME}
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

fmlxclean:	fclean
			${RM} libmlx.a
			${RM} libmlx.dylib

re:			fclean all

bonus:		${OBJS_B}
			${CC} -I${INCLS} ${CFLAGS} -o ${NAME} ${OBJS_B}

.PHONY:		all clean fclean re
