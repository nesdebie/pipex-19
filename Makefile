NAME	= pipex

SRCS 	=	srcs/pipex.c \
			srcs/utils.c

SRCS_B	=	srcs/pipex_bonus.c \
			srcs/utils_bonus.c

OBJS 	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

HEADER	= includes

CC 		= cc

CFLAGS 	= -Wall -Wextra -Werror

.c.o:		%.o : %.c
					$(CC) ${CFLAGS} -I${HEADER} -c $< -o $(<:.c=.o)

all: 		${NAME}

${NAME}:	${OBJS}
					make re -C ./libft
					$(CC) ${OBJS} -Llibft -lft -o ${NAME}


bonus:		${OBJS_B}
					make re -C ./libft
					$(CC) ${OBJS_B} -Llibft -lft -o ${NAME}

clean:
					make clean -C ./libft
					rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					make fclean -C ./libft
					rm -f $(NAME)

re:			fclean all

re_bonus:	all clean fclean re bonus