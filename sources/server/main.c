/*
** main.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/sources/server
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 14:29:06 2017 Matthias Prost
** Last update	Thu Jun 15 17:49:41 2017 Full Name
*/

#include "server.h"

int	s_error(char *str)
{
  perror(str);
  exit(EXIT_FAILURE);
}

void		serverInit(t_env *env, char *port)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    {
      env->users[i].socket = -1;
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
  serverInit(&env, av[1]);
  serverLoop(&env);
  return (0);
}
