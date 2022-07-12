LIBFT_PATH = ./libft

MAKE_IN_DIRECTORY = make -C

MAKELIBFT = ${MAKE_IN_DIRECTORY} ${LIBFT_PATH}

NAME	= libftpipex.a

CPLIBFT = cp ${LIBFT_PATH}/libft.a libftpipex.a

SRCS	= check_params.c

OBJS	= ${SRCS:.c=.o}

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

AR_RCS 	= ar rcs

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${MAKELIBFT} && ${CPLIBFT} && ${AR_RCS} ${NAME} ${OBJS}  

all:		$(NAME)

clean:		
			${RM} ${OBJS}
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} clean

fclean:		clean
			${RM} ${NAME} 
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} fclean

re:		fclean all

.PHONY:		all clean fclean re
