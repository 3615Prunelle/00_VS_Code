# Name of the library
NAME = libft.a
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.  # Include current directory for headers
# Source files
SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_itoa.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c
# Object files
OBJS = $(SRCS:.c=.o)

# Bonus source files
BONUS_SRCS =	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c
# Object files for the bonus part
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Default rule to compile the library + automatic install "rule"
all: $(NAME) install
# Rule to create the static library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
# Compile bonus
bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
# Rule to compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
# Clean rule to remove object files
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
# Fclean rule to remove object files and the executable
fclean: clean
	rm -f $(NAME)
# Rule to clean and recompile everything
re: fclean all
# Mettre à jour les dossiers lib&include avec tous les .a, et les .h quand je fais 'make install' (update : pas la peine car automatisé dans 'all' donc via commande 'make')
install:
	cp libft.h ../98_include
	cp libft.a ../99_lib
# Phony targets to prevent conflicts with files
.PHONY: all clean fclean re bonus
