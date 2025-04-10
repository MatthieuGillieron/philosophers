NAME = philosophers

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCDIR = src
OBJDIR = obj

SRCS = main.c \
        philosophers.c \
        utils.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

SUCCESS = "\033[1;92m✅ Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m❌ Erreur de compilation ! ❌\033[0m"

all: $(NAME)

# Compilation de l'exécutable final

$(NAME): $(OBJS)
    @$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && echo $(SUCCESS) || echo $(FAILURE)

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

# Création du dossier obj
$(OBJDIR):
    @mkdir -p $@

 # Si le dossier n'est pas vide ou n'existe pas, la commande échoue silencieusement
 # grâce à 2>/dev/null (qui redirige les erreurs vers null) et || true (qui empêche l'arrêt du script en cas d'erreur).
clean:
    @$(RM) $(OBJS)
    @rmdir $(OBJDIR) 2>/dev/null || true

fclean: clean
    @$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re