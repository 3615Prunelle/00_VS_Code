# NB :	Makefiles must be indented using TABs and not spaces (or make will fail)
#		On déclare en premier toutes les variables dont make aura besoin pour compiler
#		Puis on définit des règles (actions) qui utilisent ces variables et éventuellement d'autres règles
#		Puis on définit les scripts à exécuter par ces règles (qui incluent eux même des variables et des commandes)
#		Je peux donner les noms que je veux aux variables et aux règles
#		Les règles clean, fclean, re et .PHONY doivent toujours être présentes
#		Les règles sont appelées par make (I chose with one, default is first one)
# VERY IMPORTANT : Vérifier l'ordre des flags/élements dans les commandes est très important et peut
#	générer des grosses erreurs à la compilation même si juste 2 éléments sont inversés
#	Par exemple, les objets doivent toujours précéder les -l pour que le linker voie ce qui doit être résolu.

# Name of the executable (program, library, etc) to be created, with or without extension
NAME =

# Compiler à utiliser
CC = cc

# Flags de compilation
#	-g			Pour pouvoir débugger facilement (points d'arrêt dans VSCode, etc)
#	-Wall		Active tous les avertissements de base
#	-Wextra		Active des avertissements supplémentaires
#	-Werror		Traite les avertissements comme des erreurs
#	-I.			Ensures that header files in the current project folder are found during compilation
#					(pas nécessaire si j'ai mis les #include "lib_truc.h" dans tous les fichiers)
#	-I			Ajoute un répertoire à aller scanner pour aller chercher des include (.h)
#					!! Bien s'assurer de mettre TOUS les répertoires !!
#				Mettre path relatif de chaque repo dans lequel on a un .h qui nous intéresse
CFLAGS = -g -Wall -Wextra -Werror -I ../repo1

# Flags de linking (séparés des flags de compilation, pour une meilleure lisibilité)
# Linking (avec un Linker) =  Dire au programme "Voilà où trouver tout ce que tu utilises"
# NB : On ne met les $(LFLAGS) que dans les commandes de l'étape de linking (pour créer un exécutable final)
#	-L			Ajoute un répertoire à aller scanner pour aller chercher des library nécessaires (.a ou .so)
#					!! Bien s'assurer de mettre TOUS les répertoires les library citées après !!
#					Ou alors, mettre toutes les library dans le même répertoire
#	-l			Ajoute une library spécifique (pas besoin d'écrire la partie 'lib', voire note ci dessous)
#	-lft		= -l ft = -l (lib)ft = Liaison avec libft.a
#					Toujours en dernier arg sinon problèmes type 'undefined reference to ft_*' (at least lors de la compilation dans VSCode via .json)
LFLAGS = -L ../repo2 -llib1 -llib2 ../repo3 -llib3 -lft

# On définit la variable des fichiers sources
#	The \ at the end of each file is very important (except for the last file), and means all files are on the same line
#		Retour à la ligne sans \ équivaut à taper sur la touche entrée (not wanted here)
SRCS = 	file1.c \
		file2.c \
		file3.c

# On définit la variable OBJS (Object files) :
#	$(SRCS)			Go to this variable
#	:.c=.o			And create a list of unitialized .o (object) files from all the .c files
# NB : It doesn't compile anything yet, it just creates 'empty' .o files to be used later ( = uninitialized variable)
#		Compilation will happen later through the '%.o' rule/target
OBJS = $(SRCS:.c=.o)

# If applicable (Penser à bien ajouter une règle 'bonus' si on utilise cette variable, et à ajuster les scripts)
BONUS_SRCS =	file1.c \
				file2.c

# Même opération que pour la variable SRCS
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# A partir de là, on a la syntaxe suivante
#		... Pour les règles:
#	[Règle (en jaune) = Nom de la commande, au choix ou fixé par 42] : [Prérequis / Dépendance(s) = Variables ou autres règles. Pas obligatoire]
#	(Ligne suivante) [Script qui s'execute] OU TAB + [Commande shell que make doit exécuter]
# NB :	Les règles sont en réalité des targets, mais comme elles correspondent à des actions, on peut les nommer règles pour éviter des confusions
#		Pour lancer une de ces règles, taper 'make + name of the rule' dans le terminal, dans le dossier où se trouve le Makefile

# 		... Pour les scripts:
#	[Target = (Généralement) Nom d’exécutable ou de fichier objet] : [Prérequis / Dépendance(s) = éléments ou code source nécessaires pour créer la target]
#	(Ligne(s) suivante(s)) TAB + [Commande shell que make doit exécuter pour construire une target]

# First rule in the Makefile = Default rule to compile the library - Runs when I type "make"
#	The 'all' rule is called by 'make' to create (NAME) after calling the ruleX
#	$() = Variable nécésssaire (dépendance) pour l'action demandée à "all"
#	ruleX = If another rule is required (as a dependency), put it here
#	Sum up : This rule tells "make" that "all" depends on (NAME) (defined earlier), so it must be built first
# 	Here, $(NAME) is a dependency, meaning that the bloc below this one (with $(NAME) as a target)
#		needs to be executed to create $(NAME), through the script 'ar rcs $(NAME) $(OBJS)'
all: $(NAME) ruleX

# First Script to create whetever I want to create (the command is customized according to the kind of executable wanted).
#		$()		This variable is the target to create
# Then, for example :
#		ar		Command to create an archive (static library) : ***.a
#		rcs		Remplace (r) ou créée (c), puis crée un sommaire (s) à mon programme pour que le linker (qui assemble l'exécutablel) trouve facilement quelle fonction est dans quel .o
#				If (NAME) already exists, it updates the object files inside
# NB : No command = Nothing will be created
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
# Another example
	$(CC) -ggdb -o $@ $(OBJS) $(LFLAGS)
# Another example (-o = output = telling the compiler which name to give to the excutable)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

# Rule to compile the source files into object files
# This rule is called automatically if/when a .o file is needed
#	%	Pour définir des règles génériques applicables à plusieurs fichiers (équivalent de *.o *.c dans le shell)
#	$<	Refers to the first dependance/prérequis of that rule (here : %.c)
#	$^	Refers to all dependances/prérequis (not applicable here because only one dependency)
#	$@	Refers to the target file of that rule (here : %.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to delete only object files
#	Removes (rm) without asking confirmation (f = force)
clean:
	rm -f $(OBJS)

# Full clean rule to delete object files (***.o) and the executable (***.a)
fclean: clean
	rm -f $(NAME)
	rm -f a.out

# Rule to delete .o and .a (fclean) and recompile everything (all)
# Like all previous rules, to run this one, type 'make re' in the terminal
re: fclean all

# Mettre à jour les dossiers lib&include avec tous les .a, et les .h quand je fais 'make install'
# Autre option : 	Cette action peut être automatisée si placée dans 'all' comme dépendance.
#					Du coup elle serait automatiquement exécutée dans la commande 'make' principale
install:
	cp ft_printf.h ../98_include
	cp libftprintf.a ../99_lib

# Marks certain targets as "phony", meaning they aren’t real files but just names for rules
# Prevents conflicts if files named all, clean, etc., exist
.PHONY: all clean fclean re install
