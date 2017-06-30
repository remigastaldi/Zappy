/*
** server.h for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/includes
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 15:09:06 2017 Matthias Prost
** Last update Fri Jun 30 15:00:47 2017 Matthias Prost
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "utilities.h"
#include "GUI.h"

#define FD_FREE		0
#define FD_CLIENT	1
#define FD_SERVER	2

#define NBR_ARGS    6
#define NBR_PARAMS  11

#define LINEMATE    3
#define DERAUMERE   2
#define SIBUR       3
#define MENDIANA    2
#define PHIRAS      3
#define THYSTAME    2
#define FOOD        5

typedef struct	    s_commands
{
  char              *command;
  void              (*p)(t_env *env, char **av, int i);
}		            t_commands;

typedef struct	    s_params
{
  char		          *params;
  void		          (*p)(t_env *env, char **msg, t_users *user);
}		                t_params;

int                 s_error(char *str);

void                printUsage();
void                print_error(char *str);

void                widthArg(t_env *env, char **av, int i);
void                heightArg(t_env *env, char **av, int i);
void                clientsNbArg(t_env *env, char **av, int i);
void                portArg(t_env *env, char **av, int i);
void                freqArg(t_env *env, char **av, int i);
void                nameArg(t_env *env, char **av, int i);

void                createServer(t_env *env);
void                createMap(t_env *env);
void                serverLoop(t_env *env);

void                addClient(t_env *env, int s);

void                forwardParam(t_env *env, char **msg, t_users *user);
void                rightParam(t_env *env, char **msg, t_users *user);
void                leftParam(t_env *env, char **msg, t_users *user);
void                lookParam(t_env *env, char **msg, t_users *user);
void                koParam(t_env *env, char **msg, t_users *user);
void                inventoryParam(t_env *env, char **msg, t_users *user);
void                takeParam(t_env *env, char **msg, t_users *user);
void                setParam(t_env *env, char **msg, t_users *user);
void                incantationParam(t_env *env, char **msg, t_users *user);
void                forkParam(t_env *env, char **msg, t_users *user);

void                forwardAction(t_env *env, char **msg, t_users *user);
void                rightAction(t_env *env, char **msg, t_users *user);
void                leftAction(t_env *env, char **msg, t_users *user);
void                connect_nbrAction(t_env *env, char **msg, t_users *user);
void                inventoryAction(t_env *env, char **msg, t_users *user);
void                takeAction(t_env *env, char **msg, t_users *user);
void                setAction(t_env *env, char **msg, t_users *user);
void                incantationAction(t_env *env, char **msg, t_users *user);
void                forkAction(t_env *env, char **msg, t_users *user);

void                lookAction(t_env *env, char **msg, t_users *user);

int                 count_number_team(char *str, t_env  *env);

t_queue             *initWorkingQueue();
t_action            *newAction(t_queue *, t_users *, void *, double ac_time);
void                addActionData(t_action *, t_env *, char **);
void                printWorkingQueue(t_queue *);
void                freeWorkingQueue(t_queue *);
int                 deleteAction(t_queue *, t_action *);

char                *cmd_look(t_env *env);

void		            addUserTab(t_env *env, int socket);
void	              removeUserTab(t_env *env, int socket);

void                free_env(t_env *env);
void                free_tab(char **tab);

void                refresh_queue(t_env *env);
void                refresh_player_food(t_env *env);

extern t_commands g_commands[NBR_ARGS];

#endif
