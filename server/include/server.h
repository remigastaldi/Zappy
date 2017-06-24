/*
** server.h for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/includes
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 15:09:06 2017 Matthias Prost
** Last update Sat Jun 24 15:50:07 2017 Matthias Prost
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "utilities.h"
#include "GUI.h"

#define FD_FREE		0
#define FD_CLIENT	1
#define FD_SERVER	2

#define NBR_ARGS    6
#define NBR_PARAMS  3

#define LINEMATE    3
#define DERAUMERE   2
#define SIBUR       3
#define MENDIANA    2
#define PHIRAS      3
#define THYSTAME    2

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

t_queue             *initWorkingQueue();
void                newAction(t_queue *, t_users *, enum Action, int);
void                printWorkingQueue(t_queue *);
void                freeWorkingQueue(t_queue *);
int                 deleteAction(t_queue *, int);

extern t_commands g_commands[NBR_ARGS];

#endif
