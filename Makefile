##
## Makefile for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy
##
## Made by Matthias Prost
## Login   <matthias.prost@epitech.eu>
##
## Started on  Thu Jun 15 14:35:28 2017 Matthias Prost
## Last update Thu Jun 15 15:14:31 2017 Matthias Prost
##

CC 					=		gcc

NAME_SERVER	=		zappy_server

NAME_AI			=		zappy_ai

ECHO    		=		/bin/echo -e \

DEFAULT			=		"\033[00m"
GREEN				=		"\033[0;32m"
TEAL				= 	"\033[1;36m"
RED					=		"\033[5;31m"

CFLAGS			+=	-Wextra -Wall -Werror -W
CFLAGS			+=  -I./includes/

SRC_SERVER	+=	sources/server/main.c

SRC_AI	+=	sources/ai/main.c

SRC_UTILS		+=	sources/utilities/get_next_line.c

OBJ_SERVER	=		$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=		$(SRC_AI:.c=.o)

OBJ_UTILS		=		$(SRC_UTILS:.c=.o)

all:						$(NAME_SERVER) $(NAME_AI)

$(NAME_SERVER):	$(OBJ_SERVER)
								@$(CC) $(CFLAGS) $(SRC_SERVER) $(SRC_UTILS) -o $(NAME_SERVER)
								@$(ECHO) $(GREEN) "[OK]" $(NAME_SERVER) $(TEAL) $(DEFAULT)

$(NAME_AI):	$(OBJ_CLIENT)
								@$(CC) $(CFLAGS) $(SRC_AI) $(SRC_UTILS) -o $(NAME_AI)
								@$(ECHO) $(GREEN) "[OK]" $(NAME_AI) $(TEAL) $(DEFAULT)

clean:
								@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean:					clean
								@rm -f $(NAME_SERVER) $(NAME_AI)

re: 						fclean all

.c.o:
								@$(CC) $(CFLAGS) -c -o $@ $< && \
								$(ECHO) $(GREEN) "[OK]" $(TEAL) $^ $(DEFAULT) || \
								$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)

.PHONY: 				all clean fclean re
