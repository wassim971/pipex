NAME = pipex

SRC =  $(addprefix srcs/, pipex.c pipex_utils.c)

SRCS = ${SRC}

OBJS = ${SRCS:.c=.o}

INCLUDE = -Iinclude

CC = cc -g3

CFLAGS = -Wall -Werror -Wextra

LIBFTPATH = libft

LIBFT = $(LIBFTPATH)/libft.a

FT_PRINTF_PATH = ft_printf

FT_PRINTF = $(FT_PRINTF_PATH)/libftprintf.a

.c.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o} 

$(NAME) : $(OBJS) $(LIBFT) $(FT_PRINTF)
	${CC} ${CFLAGS}${INCLUDE} $^ -o $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFTPATH)

$(FT_PRINTF) : 
	$(MAKE) -C $(FT_PRINTF_PATH)

all: ${NAME}

clean:
	rm -f ${OBJS}
	$(MAKE) clean -C $(FT_PRINTF_PATH)
	$(MAKE) clean -C $(LIBFTPATH)

fclean: clean
	rm -f ${NAME}
	$(MAKE) fclean -C $(FT_PRINTF_PATH)
	$(MAKE) fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re