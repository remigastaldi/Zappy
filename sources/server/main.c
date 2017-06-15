/*
** main.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/sources/server
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 14:29:06 2017 Matthias Prost
** Last update	Thu Jun 15 17:45:57 2017 Full Name
*/

#include "server.h"

void		mainInit(t_env *env, char *port)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    {
      env->users[i].socket = -1;
      env->users[i].nick = NULL;
      env->users[i].chan = strdup("general");
    }
  memset(env->fd_type, FD_FREE, MAX_FD);
  env->port = atoi(port);
  createServer(env);
}

int		printUsage(char *binName)
{
  printf("Usage: %s [PORT]\n", binName);
  return (-1);
}

int		main(int ac, char **av)
{
  t_env		env;

  if (ac != 2 || strcmp(av[1], "--help") == 0)
    return (printUsage(av[0]));
  mainInit(&env, av[1]);
  serverLoop(&env);
  return (0);
}
