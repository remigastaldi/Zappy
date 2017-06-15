/*
** server.h for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/includes
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 15:09:06 2017 Matthias Prost
** Last update	Thu Jun 15 19:52:26 2017 Full Name
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "utilities.h"

#define FD_FREE			0
#define FD_CLIENT		1
#define FD_SERVER		2
#define MAX_FD			255

#define NBR_ARGS    5

typedef void(*fct)();

typedef struct			s_users
{
  int				        socket;
}				            t_users;

typedef struct		  s_env
{
  int				        port;
  int               width;
  int               height;
  char              **names;
  int               clientsNb;
  int               freq;
  t_users		        users[MAX_FD];
  char			        fd_type[MAX_FD];
  fct				        fct_read[MAX_FD];
  fct				        fct_write[MAX_FD];
}				            t_env;

typedef struct	    s_commands
{
  char		          *command;
  void		          (*p)(t_env *env, char **av, int i);
}		                t_commands;

int	    s_error(char *str);

void		printUsage();

void    widthArg(t_env *env, char **av, int i);
void    heightArg(t_env *env, char **av, int i);
void    clientsNbArg(t_env *env, char **av, int i);
void    portArg(t_env *env, char **av, int i);
void    freqArg(t_env *env, char **av, int i);

void		createServer(t_env *env);
void		serverLoop(t_env *env);

void		addClient(t_env *env, int s);

extern t_commands g_commands[NBR_ARGS];

#endif
