LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

CLIENT_SRC = main.c transmit.c utils.c
CLIENT_DIR = client/src
CLIENT_OBJ_DIR = client/obj
CLIENT_SRC_FILES = $(addprefix $(CLIENT_DIR)/, $(CLIENT_SRC))
CLIENT_OBJ = $(addprefix $(CLIENT_OBJ_DIR)/, $(CLIENT_SRC:.c=.o))
CLIENT = bin/client

SERVER_SRC = main.c
SERVER_DIR = server/src
SERVER_OBJ_DIR = server/obj
SERVER_SRC_FILES = $(addprefix $(SERVER_DIR)/, $(SERVER_SRC))
SERVER_OBJ = $(addprefix $(SERVER_OBJ_DIR)/, $(SERVER_SRC:.c=.o))
SERVER = bin/server

CFLAGS = -Wall -Wextra -Werror -Iinclude
INCLUDE = -I include -I $(LIBFT_DIR)/include
LIBS = -L $(LIBFT_DIR) -lft

YELLOW = \033[0;33m
RESET = \033[0m
SERVER_PREFIX = $(YELLOW)[$(SERVER)]$(RESET)
CLIENT_PREFIX = $(YELLOW)[$(CLIENT)]$(RESET)

all: $(LIBFT) $(CLIENT) $(SERVER)

$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_DIR)/%.c
	@mkdir -p $(CLIENT_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(CLIENT_PREFIX) Compiling: $<"

$(SERVER_OBJ_DIR)/%.o: $(SERVER_DIR)/%.c
	@mkdir -p $(SERVER_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(SERVER_PREFIX) Compiling: $<"

$(CLIENT): $(CLIENT_OBJ)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(INCLUDE) $(CLIENT_OBJ) $(LIBS) -o $(CLIENT)
	@echo "$(CLIENT_PREFIX) Link complete: $(CLIENT)"

$(SERVER): $(SERVER_OBJ)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(INCLUDE) $(SERVER_OBJ) $(LIBS) -o $(SERVER)
	@echo "$(SERVER_PREFIX) Link complete: $(SERVER)"

$(LIBFT):
	@echo "$(PREFIX) Building library: libft"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@rm -rf $(SERVER_OBJ_DIR) $(CLIENT_OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)Cleaned objects"

fclean: clean
	@rm -rf bin
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(YELLOW)Removed executables."

re: fclean all

.PHONY: all clean fclean re
