NAME		=	philo
CCF			=	gcc $(CFLAGS)
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -I./includes -g3
SRC_PATH	=	sources/
SRC_FILES	=	philo_main.c parse_params.c start_philos.c philosopher.c philo_utils.c philos_life.c utils.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC_FILES))
OBJS		=	$(SRCS:.c=.o)
HDR			=	includes/philo_main.h
CYAN		=	\x1B[36m
MAGENTA		=	\x1B[35m
GREEN		=	\033[92m
ENDCOLOR	=	\x1B[0m

all:		$(NAME)

$(NAME):	$(OBJS) $(HDR)
			@$(CCF) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "${GREEN}"$(NAME)" is compiled${ENDCOLOR}"

linux:		$(OBJS) $(HDR)
			@$(CCF) $(OBJS) $(LIBFT) -o $(NAME) -lpthread
			@echo $(NAME) is compiled

clean:
			@$(RM) $(OBJS)
			@echo objs deleted

fclean:		clean
			@$(RM) $(NAME)
			@echo $(NAME) deleted

re:			fclean all

%.o:		%.c $(HDR)
			@$(CCF) -c $< -o $@
			@echo $@ compilled

norm:
			norminette $(SRCS) ./includes

.PHONY:		all clean fclean re so bonus norm