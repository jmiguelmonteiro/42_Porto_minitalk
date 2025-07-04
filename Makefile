# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 15:17:48 by josemigu          #+#    #+#              #
#    Updated: 2025/07/04 12:35:48 by josemigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
CLIENT		= client
SERVER		= server
CLIENT_B	= client
SERVER_B	= server

# Compiler
CC				= cc
CFLAGS			= -Werror -Wextra -Wall -g

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./includes/ \
				-I ./libft/includes/

# Sources
SRC_PATH_CLI	=	src_client/
SRC_PATH_SRV	=	src_server/
SRC_CLI			=	client.c
SRC_SRV			=	server.c
SRC_CLI_B		=	client_bonus.c
SRC_SRV_B		=	server_bonus.c

# Objects
OBJ_PATH_CLI	= obj_client/
OBJ_PATH_SRV	= obj_server/
OBJ_CLI			= $(SRC_CLI:.c=.o)
OBJ_SRV			= $(SRC_SRV:.c=.o)
OBJ_CLI_B		= $(SRC_CLI_B:.c=.o)
OBJ_SRV_B		= $(SRC_SRV_B:.c=.o)
OBJS_CLI		= $(addprefix $(OBJ_PATH_CLI), $(OBJ_CLI))
OBJS_SRV		= $(addprefix $(OBJ_PATH_SRV), $(OBJ_SRV))
OBJS_CLI_B		= $(addprefix $(OBJ_PATH_CLI), $(OBJ_CLI_B))
OBJS_SRV_B		= $(addprefix $(OBJ_PATH_SRV), $(OBJ_SRV_B))

all: $(LIBFT) $(CLIENT) $(SERVER)

bonus: $(LIBFT) $(CLIENT_B) $(SERVER_B)

$(OBJ_PATH_CLI)%.o: $(SRC_PATH_CLI)%.c | $(OBJ_PATH_CLI)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH_SRV)%.o: $(SRC_PATH_SRV)%.c | $(OBJ_PATH_SRV)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS_CLI): $(OBJ_PATH_CLI)

$(OBJS_SRV): $(OBJ_PATH_SRV)

$(OBJS_CLI_B): $(OBJ_PATH_CLI)

$(OBJS_SRV_B): $(OBJ_PATH_SRV)

$(OBJ_PATH_CLI):
	mkdir $(OBJ_PATH_CLI)

$(OBJ_PATH_SRV):
	mkdir $(OBJ_PATH_SRV)

$(LIBFT):
	make -sC $(LIBFT_PATH)

$(CLIENT): $(OBJS_CLI)
	@echo "Compiling minitalk client..."
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLI) $(LIBFT) $(INC)
	@echo "Client compiled!!!"

$(SERVER): $(OBJS_SRV)
	@echo "Compiling minitalk server..."
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SRV) $(LIBFT) $(INC)
	@echo "Server compiled!!!"

$(CLIENT_B): $(OBJS_CLI_B)
	@echo "Compiling minitalk client (bonus)..."
	$(CC) $(CFLAGS) -o $(CLIENT_B) $(OBJS_CLI_B) $(LIBFT) $(INC)
	@echo "Client compiled!!!"

$(SERVER_B): $(OBJS_SRV_B)
	@echo "Compiling minitalk server (bonus)..."
	$(CC) $(CFLAGS) -o $(SERVER_B) $(OBJS_SRV_B) $(LIBFT) $(INC)
	@echo "Server compiled!!!"
	
clean:
	@echo "Removing .o object files..."
	rm -rf $(OBJ_PATH_CLI)
	rm -rf $(OBJ_PATH_SRV)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing binaries..."
	rm -f $(CLIENT)
	rm -f $(SERVER)
	rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean bonus
