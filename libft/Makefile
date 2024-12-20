SRCS = ft_putstr_fd.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_memchr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_strlcat.c ft_toupper.c ft_tolower.c \
       ft_putchar_fd.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_memcmp.c \
       ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
       ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strncmp.c \
	   ft_putchar.c ft_putnbr.c ft_strjoin_double_ptr.c

BSRCS = ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c \
			ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstdelone_bonus.c
OBJECTS = ${SRCS:.c=.o}
BOBJECTS = ${BSRCS:.c=.o}
HEADERS = libft.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
LIBC = ar rcs

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJECTS}
	${LIBC} ${NAME} ${OBJECTS}

bonus: ${OBJECTS} ${BOBJECTS}
	${LIBC} ${NAME} ${BOBJECTS}

clean:
	rm -f ${OBJECTS} ${BOBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all re clean fclean bonus
