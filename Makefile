LIBFT_PATH = ./libft

MAKE_IN_DIRECTORY = make -C

MAKELIBFT = ${MAKE_IN_DIRECTORY} ${LIBFT_PATH}

NAME = pipex

NAME_BONUS = pipex_bonus

SRCS	= pipex.c error_handling.c 

SRCS_BONUS	= pipex_bonus.c pipex_utils_bonus.c error_handling_bonus.c

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

LIBFTPATH = ./libft/libft.a

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} $(LIBFTPATH)
			${CC} ${OBJS} $(LIBFTPATH) -o $(NAME)

$(NAME_BONUS):	${OBJS_BONUS} $(LIBFTPATH)
				${CC} ${OBJS_BONUS} $(LIBFTPATH) -o $(NAME_BONUS)

$(LIBFTPATH): 
			${MAKELIBFT}

bonus: ${NAME_BONUS}

all:		$(NAME)

clean:		
			${RM} ${OBJS} ${OBJS_BONUS}
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} clean

fclean:		clean
			${RM} ${NAME} ${NAME_BONUS}
			${MAKE_IN_DIRECTORY} ${LIBFT_PATH} fclean

re:		fclean all

.PHONY:		all clean fclean re bonus
