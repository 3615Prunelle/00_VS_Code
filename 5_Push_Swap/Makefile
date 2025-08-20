# Modifs de config pour évals :
# Créer un dossier par librairie, dans le projet actuel, et y placer :
#		La sélection de fonctions utilisées (ou tout mettre)
#		Son Makefile
#		Son .h
# Updater le Makefile + .h de chaque librairie (fonctions, bonus, règles etc si nécessaire)
# Dans le Makefile du projet, créer une règle (par librairie) pour compiler les librairies nécessaires au projet
# Mettre cette règle comme dépendance dans le script qui va compiler mon projet actuel
# Mettre le dossier où se trouvent les .h et .a dans les flags de compilation de mon projet actuel

NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I ./libft -I ./ft_printf
LFLAGS = -L ./libft -L ./ft_printf -lftprintf -lft

SRCS = 	push_swap_main.c \
		push_swap_input_management.c \
		push_swap_check_and_exit.c \
		push_swap_operations.c \
		push_swap_lst_functions.c \
		push_swap_algorithms.c \
		push_swap_tools.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# Créer une règle pour Make les executables de libft et printf
# $(MAKE) est une variable fournie automatiquement par le programme make (pas besoin de la créer)
# -C (= Change directory) est un flag de make, qui équivaut à :
# "Va dans ce dossier, exécute le Makefile qui est dedans, puis reviens au dossier courant”
create_libft :
	$(MAKE) -C ./libft

create_printf :
	$(MAKE) -C ./ft_printf

# Ajouté les deux règles en dépendance de $(NAME)
$(NAME): $(OBJS)	create_libft create_printf
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

# Ajouté des commandes pour que fclean nettoie les sous dossiers
fclean: clean
	rm -f $(NAME)
	rm -f a.out
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
