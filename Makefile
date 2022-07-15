LIBFT_PATH = ./libft

MAKE_IN_DIRECTORY = make -C

MAKELIBFT = ${MAKE_IN_DIRECTORY} ${LIBFT_PATH}

NAME	= pipex

LIBNAME = libftpipex.a

CPLIBFT = cp ${LIBFT_PATH}/libft.a libftpipex.a

SRCS	= check_params.c freeargs.c 

OBJS	= ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

AR_RCS 	= ar rcs

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${MAKELIBFT} && ${CPLIBFT} && ${AR_RCS} ${LIBNAME} ${OBJS}
			${CC} pipex.c ${LIBNAME} -o ${NAME}

all:		$(NAME)

clean:		
			${RM} ${OBJS}
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} clean

fclean:		clean
			${RM} ${LIBNAME} 
			${RM} ${NAME} 
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} fclean

re:		fclean all

.PHONY:		all clean fclean re
