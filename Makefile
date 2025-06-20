# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josemigu <josemigu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 15:17:48 by josemigu          #+#    #+#              #
#    Updated: 2025/06/20 18:08:10 by josemigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME_CLIENT	= client
NAME_SERVER	= server

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
SRCS_CLI		=	$(addprefix $(SRC_PATH_CLI), $(SRC_CLIENT))
SRCS_SRV		=	$(addprefix $(SRC_PATH_SRV), $(SRC_SERVER))

# Objects
OBJ_PATH_CLI	= obj_client/
OBJ_PATH_SRV	= obj_server/
OBJ_CLI			= $(SRC_CLI:.c=.o)
OBJ_SRV			= $(SRC_SRV:.c=.o)
OBJS_CLI		= $(addprefix $(OBJ_PATH_CLI), $(OBJ_CLI))
OBJS_SRV		= $(addprefix $(OBJ_PATH_SRV), $(OBJ_SRV))

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(OBJ_PATH_CLI)%.o: $(SRC_PATH_CLI)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH_SRV)%.o: $(SRC_PATH_SRV)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS_CLI): $(OBJ_PATH_CLI)

$(OBJS_SRV): $(OBJ_PATH_SRV)

$(OBJ_PATH_CLI):
	@mkdir $(OBJ_PATH_CLI)

$(OBJ_PATH_SRV):
	@mkdir $(OBJ_PATH_SRV)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

$(NAME_CLIENT): $(OBJS_CLI)
	@echo "Compiling minitalk client..."
	@$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLI) $(LIBFT) $(INC)
	@echo "Client ready!!!"

$(NAME_SERVER): $(OBJS_SRV)
	@echo "Compiling minitalk server..."
	@$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SRV) $(LIBFT) $(INC)
	@echo "Server ready!!!"

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH_CLI)
	@rm -rf $(OBJ_PATH_SRV)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing test..."
	@rm -f $(NAME_CLIENT)
	@rm -f $(NAME_SERVER)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean
