# Name of the library that will be created
NAME = libgetnextline.a

# Compiler and flags
CC = cc
# -I. ensures that header files in the current project folder are found during compilation
CFLAGS = -Wall -Wextra -Werror -I.

# Source files
SRCS = 	get_next_line.c \
		get_next_line_utils.c \

# Object files - $(VARIABLENAME) means "use the value of the VARIABLENAME variable".
OBJS = $(SRCS:.c=.o) # Converts .c SRCS files to .o objects files

# Default rule to compile the library - Runs when I type "make" - Calls the rule (below) to create NAME
# This tells Make that all depends on ***.a, so it must be built first
all: $(NAME) install

# Rule to create the static library
#ar →	Command to create an archive (static library) : ***.a
#rcs →	Create (c), replace (r), and add a symbol table index (s)
# If ***.a already exists, it updates the object files inside
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Rule to compile the source files into object files
# $< Refers to the source file (***.c) / $@ Refers to the target file (***.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to delete only object files - Type make clean
clean:
	rm -f $(OBJS)

# Full clean rule to delete object files (***.o) and the executable (***.a) - make fclean
fclean: clean
	rm -f $(NAME)
	rm -f a.out

# Rule to delete .o and .a (fclean) and recompile everything (all) - make re
re: fclean all

# Mettre à jour les dossiers lib&include avec tous les .a, et les .h quand je fais 'make install' (update : pas la peine car automatisé dans 'all' donc via commande 'make')
install:
	cp get_next_line.h ../98_include
	cp libgetnextline.a ../99_lib

# Prevents conflicts if files named all, clean, etc., exist
# Ensures make always runs these rules
# Marks certain targets as "phony", meaning they aren’t real files but just names for commands
.PHONY: all clean fclean re
