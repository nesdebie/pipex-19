NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	mandatory/pipex.c\
		mandatory/utils.c\
		libft/libft.a

SRCS_BONUS = 	bonus/pipex_bonus.c\
				bonus/utils_bonus.c\
				libft/libft.a\

$(NAME) :
	make all -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all

bonus : clean
	make all -C libft
	gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)

.PHONY: all clean fclean re bonus