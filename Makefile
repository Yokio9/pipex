SRCS = pipex.c ./libft/ft_calloc.c ./libft/ft_bzero.c ./libft/ft_memset.c ./libft/ft_strncmp.c
OBJECTS = ${SRCS:.c=.o}
HEADERS = pipex.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I.
LDFLAGS = -fsanitize=address
NAME = pipex
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	cd $(LIBFT_PATH) && make

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(LDFLAGS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean