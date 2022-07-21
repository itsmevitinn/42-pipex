LIBFT_PATH = ./libft

MAKE_IN_DIRECTORY = make -C

MAKELIBFT = ${MAKE_IN_DIRECTORY} ${LIBFT_PATH}

NAME	= pipex

NAME_BONUS	= pipex_bonus

LIBNAME = libftpipex.a

CPLIBFT = cp ${LIBFT_PATH}/libft.a libftpipex.a

SRCS	= doexecve.c close_all.c error_msg.c 

OBJS	= ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

AR_RCS 	= ar rcs

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${MAKELIBFT} && ${CPLIBFT} && ${AR_RCS} ${LIBNAME} ${OBJS}
			${CC} ${NAME}.c ${LIBNAME} -o ${NAME}

bonus:		${OBJS}
			${MAKELIBFT} && ${CPLIBFT} && ${AR_RCS} ${LIBNAME} ${OBJS}
			${CC} ${NAME_BONUS}.c ${LIBNAME} -o ${NAME_BONUS}

all:		$(NAME)

clean:		
			${RM} ${OBJS}
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} clean

fclean:		clean
			${RM} ${LIBNAME}
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} fclean

re:		fclean all

.PHONY:		all clean fclean re
