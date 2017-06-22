##
## Makefile for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy
##
## Made by Matthias Prost
## Login   <matthias.prost@epitech.eu>
##
## Started on  Thu Jun 15 14:35:28 2017 Matthias Prost
## Last update Wed Jun 21 23:56:02 2017 gastal_r
##

.DEFAULT_GOAL := all

OS					=		$(shell uname -s)

CC 					=		gcc
CXX 				=		g++ -std=c++11

NAME_SERVER	=		"zappy_server"

NAME_AI			=		"zappy_ai"

ifeq ($(OS), Darwin)
	ECHO      =   echo
else
	ECHO      =   /bin/echo -e
endif

DEFAULT			=		"\033[00m"
GREEN				=		"\033[0;32m"
TEAL				= 	"\033[1;36m"
RED					=		"\033[5;31m"

CFLAGS			+=	-Wextra -Wall -Werror -W -g -g3
CFLAGS			+=  -I./server/include/

CXXFLAGS		+=	-O3 -Wextra -Wall -Werror -W -g -g3
CXXFLAGS		+=  -I./ai/include/

SRC_SERVER	+=	server/src/main.c
SRC_SERVER	+=	server/src/server_loop.c
SRC_SERVER	+=	server/src/client.c
SRC_SERVER	+=	server/src/args_commands.c
SRC_SERVER	+=	server/src/name_command.c
SRC_SERVER	+=	server/src/map.c

SRC_AI			+=	ai/src/main.cpp
SRC_AI			+=	ai/src/Ai.cpp

SRC_UTILS		+=	server/src/utilities/get_next_line.c
SRC_UTILS		+=	server/src/utilities/epur.c
SRC_UTILS		+=	server/src/utilities/errors.c
SRC_UTILS		+=	server/src/utilities/print.c
SRC_UTILS		+=	server/src/utilities/memories.c

OBJ_SERVER	=		$(SRC_SERVER:.c=.o)
OBJ_UTILS		=		$(SRC_UTILS:.c=.o)

OBJ_AI			=		$(SRC_AI:.cpp=.o)

$(NAME_SERVER)	:		$(OBJ_SERVER)
										@$(CC) $(CFLAGS) $(SRC_SERVER) $(SRC_UTILS) -o $(NAME_SERVER)

$(NAME_AI)      :		$(OBJ_AI)
										@$(CXX) $(CXXFLAGS) $(SRC_AI) -o $(NAME_AI)

all							:		$(NAME_AI) $(NAME_SERVER)

zappy_server    :   $(NAME_SERVER)

zappy_ai        :   $(NAME_AI)

clean						:
										@rm -f $(OBJ_SERVER) $(OBJ_AI)

fclean					:		clean
										@rm -f $(NAME_SERVER) $(NAME_AI)

re							:		fclean all

.c.o						:
										@$(CC) $(CFLAGS) -c -o $@ $< && \
										$(ECHO) $(GREEN) "[OK]" $(TEAL) $^ $(DEFAULT) || \
										$(ECHO) $(RED) "[ERROR]" $(TEAL) $^ $(DEFAULT)

.cpp.o					:
										@$(CXX) $(CXXFLAGS) -c -o $@ $< && \
										$(ECHO) $(GREEN) "[OK]" $(TEAL) $^ $(DEFAULT) || \
										$(ECHO) $(RED) "[ERROR]" $(TEAL) $^ $(DEFAULT)

.PHONY					:		all zappy_server zappy_ai clean fclean re
