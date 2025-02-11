CLIENT_SRC = main.c
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

all: $(CLIENT) $(SERVER)

$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_DIR)/%.c
	@mkdir -p $(CLIENT_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(YELLOW)[$(CLIENT)] Compiled $<$(RESET)"

$(SERVER_OBJ_DIR)/%.o: $(SERVER_DIR)/%.c
	@mkdir -p $(SERVER_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(YELLOW)[$(SERVER)] Compiled $<$(RESET)"

$(CLIENT): $(CLIENT_OBJ)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(INCLUDE) $(CLIENT_OBJ) -o $(CLIENT)
	@echo "$(GREEN)[$(CLIENT)] Compilation successful!$(RESET)"

$(SERVER): $(SERVER_OBJ)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(INCLUDE) $(SERVER_OBJ) -o $(SERVER)
	@echo "$(GREEN)[$(SERVER)] Compilation successful!$(RESET)"

clean:
	@rm -rf $(SERVER_OBJ_DIR) $(CLIENT_OBJ_DIR)
	@echo "$(YELLOW)Cleaned object files.$(RESET)"

fclean: clean
	@rm -rf bin
	@echo "$(YELLOW)Removed executables.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
