##
## Makefile for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy
##
## Made by Matthias Prost
## Login   <matthias.prost@epitech.eu>
##
## Started on  Thu Jun 15 14:35:28 2017 Matthias Prost
## Last update Sun Jun 25 22:36:12 2017 Cyril Puccio
##

.DEFAULT_GOAL := all

OS					=		$(shell uname -s)

ifeq ($(OS), Darwin)
	CC 				=		gcc-7
	CXX 			=		g++-7
	ECHO      =   echo
else
	CC 				=		gcc
	CXX 			=		g++
	ECHO      =   /bin/echo -e
endif

NAME_SERVER	=		"zappy_server"

NAME_AI			=		"zappy_ai"

DEFAULT			=		"\033[00m"
GREEN				=		"\033[0;32m"
TEAL				= 	"\033[1;36m"
RED					=		"\033[5;31m"

CFLAGS			+=	-Wextra -Wall -Werror -W -g -g3
CFLAGS			+=  -I./server/include/
CFLAGS			+=	-lcsfml-graphics -lcsfml-window -lcsfml-system

CXXFLAGS		+=	-O3 -Wextra -Wall -Werror -W -g -g3
CXXFLAGS		+=  -I./ai/include/

SRC_SERVER	+=	server/src/main.c
SRC_SERVER	+=	server/src/server_loop.c
SRC_SERVER	+=	server/src/client.c
SRC_SERVER	+=	server/src/args_commands.c
SRC_SERVER	+=	server/src/name_command.c
SRC_SERVER	+=	server/src/map.c
SRC_SERVER	+=	server/src/GUI.c
SRC_SERVER	+=	server/src/params_actions.c
SRC_SERVER	+=	server/src/workingQueue.c
SRC_SERVER	+=	server/src/look.c

SRC_AI			+=	ai/src/main.cpp
SRC_AI			+=	ai/src/Ai.cpp
SRC_AI 			+= 	ai/src/Communication.cpp

SRC_UTILS		+=	server/src/utilities/get_next_line.c
SRC_UTILS		+=	server/src/utilities/epur.c
SRC_UTILS		+=	server/src/utilities/errors.c
SRC_UTILS		+=	server/src/utilities/print.c
SRC_UTILS		+=	server/src/utilities/memories.c
SRC_UTILS		+=	server/src/utilities/get_user.c
SRC_UTILS		+=	server/src/utilities/to_wordtab.c
SRC_UTILS		+=	server/src/utilities/my_strcat.c

OBJ_SERVER	=		$(SRC_SERVER:.c=.o)
OBJ_UTILS		=		$(SRC_UTILS:.c=.o)

OBJ_AI			=		$(SRC_AI:.cpp=.o)

$(NAME_SERVER)	:		$(OBJ_SERVER) $(OBJ_UTILS)
										@$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_UTILS) -o $(NAME_SERVER)

$(NAME_AI)      :		$(OBJ_AI)
										@$(CXX) $(CXXFLAGS) $(SRC_AI:.cpp=.o) -o $(NAME_AI)

all							:		$(NAME_AI) $(NAME_SERVER)

rezappy_server    :  fclean $(NAME_SERVER)

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
