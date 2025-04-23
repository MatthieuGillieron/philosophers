NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SRC_CORE = core
SRC_SIM = simulation
SRC_SYNC = sync
SRC_IO = io
SRC_UTILS = utils

SRC_CORE_FILES = main.c init.c
SRC_SIM_FILES = dinner.c monitor.c
SRC_SYNC_FILES = synchro.c getter_setter.c
SRC_IO_FILES = parsing.c write.c
SRC_UTILS_FILES = utils.c u_time.c u_mtx_thread.c

SRCS =  $(addprefix $(SRCDIR)/$(SRC_CORE)/, $(SRC_CORE_FILES)) \
        $(addprefix $(SRCDIR)/$(SRC_SIM)/, $(SRC_SIM_FILES)) \
        $(addprefix $(SRCDIR)/$(SRC_SYNC)/, $(SRC_SYNC_FILES)) \
        $(addprefix $(SRCDIR)/$(SRC_IO)/, $(SRC_IO_FILES)) \
        $(addprefix $(SRCDIR)/$(SRC_UTILS)/, $(SRC_UTILS_FILES))

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OBJ_DIRS = $(OBJDIR) \
           $(OBJDIR)/$(SRC_CORE) \
           $(OBJDIR)/$(SRC_SIM) \
           $(OBJDIR)/$(SRC_SYNC) \
           $(OBJDIR)/$(SRC_IO) \
           $(OBJDIR)/$(SRC_UTILS)

SUCCESS = "\033[1;92m✅ Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m❌ Erreur de compilation ! ❌\033[0m"

all: $(OBJ_DIRS) $(NAME)

$(OBJ_DIRS):
	@mkdir -p $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && echo $(SUCCESS) || echo $(FAILURE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR) 2>/dev/null || true

fclean: clean
	@$(RM) $(NAME)

re: fclean all
