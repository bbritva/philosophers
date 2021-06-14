NAME		=	philo
LIBFT		=	libft.a
CCF			=	gcc $(CFLAGS)
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g -I./includes
SRC_PATH	=	sources/
SRC_FILES	=	philo_one.c parse_params.c do_philos.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC_FILES))
OBJS		=	$(SRCS:.c=.o)
LIB_DIR		=	libft/
HDR			=	includes/*.h
CYAN		=	\x1B[36m
MAGENTA		=	\x1B[35m
GREEN		=	\033[92m
ENDCOLOR	=	\x1B[0m

all:		$(NAME)

$(NAME):	$(OBJS) $(HDR)
			@make bonus -C $(LIB_DIR)
			@mv $(LIB_DIR)$(LIBFT) $(LIBFT)
			@$(CCF) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "${GREEN}"$(NAME)" is compiled${ENDCOLOR}"

linux:		$(OBJS) $(HDR)
			@make bonus -C $(LIB_DIR)
			@mv $(LIB_DIR)$(LIBFT) $(LIBFT)
			@$(CCF) $(OBJS) $(LIBFT) -o $(NAME)
			@echo $(NAME) is compiled

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(LIBFT)
			@$(RM) $(OBJS)
			@echo objs deleted

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) $(NAME)
			@echo $(NAME) deleted

re:			fclean all

%.o:		%.c $(HDR)
			@$(CCF) -c $< -o $@
			@echo $@ compilled

norm:
			norminette $(SRCS) ./includes

.PHONY:		all clean fclean re so bonus norm