NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

bsrc =	pipex_bonus.c\
		pipex_utils.c

src =	pipex.c\
		pipex_utils.c
B_NAME = pipex_bonus
B_OBJS = ${bsrc:.c=.o}		
OBJS = ${src:.c=.o}
REMOVE = rm -f
LIBFT = libftps.a
LDIR = libftps/

${NAME}:${OBJS} ${LDIR}${LIBFT}
		$(CC) $(CFLAGS) $(src) ${LDIR}${LIBFT} -o $(NAME)

all:${LDIR}${LIBFT} ${NAME}

${LDIR}${LIBFT}:
	${MAKE} -C ${LDIR}

bonus :${LDIR}${LIBFT} ${B_NAME}

${B_NAME}:${B_OBJS} ${LDIR}${LIBFT}
			$(CC) $(CFLAGS) $(bsrc) ${LDIR}${LIBFT} -o $(B_NAME)


clean :
		${REMOVE} ${B_OBJS}
		${REMOVE} ${OBJS}
		${REMOVE} ${LDIR}*.o

fclean :clean
		${REMOVE} ${B_NAME}
		${REMOVE} ${NAME}
		${REMOVE} ${LDIR}${LIBFT}
re:fclean all
 
.PHONY: all clean fclean re

#LEAK_CHECK  := --leak-check=full
#LEAK_KIND   := --show-leak-kinds=all
#CHILDREN    := --trace-children=yes
#FD_TRACK    := --track-fds=yes