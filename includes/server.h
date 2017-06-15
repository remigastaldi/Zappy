/*
** server.h for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/includes
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 15:09:06 2017 Matthias Prost
** Last update	Thu Jun 15 17:44:10 2017 Full Name
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "utilities.h"

#define FD_FREE			0
#define FD_CLIENT		1
#define FD_SERVER		2
#define MAX_FD			255

typedef void(*fct)();

typedef struct			s_users
{
  int				socket;
  char				*nick;
  char				*chan;
}				t_users;

typedef struct			s_env
{
  int				port;
  t_users			users[MAX_FD];
  char				fd_type[MAX_FD];
  fct				fct_read[MAX_FD];
  fct				fct_write[MAX_FD];
}				t_env;

void		createServer(t_env *env);
void		serverLoop(t_env *env);

void		addClient(t_env *env, int s);

#endif
