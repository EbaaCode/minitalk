# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Library name
LIB_NAME = libft
NAME = $(LIB_NAME).a

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = \
	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
	ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_atol.c ft_isalpha.c \
	ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
	ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c \
	ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c \
	ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c \
	ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_striteri.c ft_strtrim.c \
	ft_print.c ft_printf.c ft_decimal.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Include
INCLUDE = -I include

# Console colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

# Build library
all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)[$(LIB_NAME)] Compilation successful!$(RESET)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(YELLOW)[$(LIB_NAME)] Compiled $<$(RESET)"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)[$(LIB_NAME)] Cleaned object files.$(RESET)"

# Full clean
fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)[$(LIB_NAME)] Removed $(NAME).$(RESET)"

# Rebuild
re: fclean all

.PHONY: all clean fclean re
