/*
** main.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/sources/server
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 14:29:06 2017 Matthias Prost
** Last update Fri Jun 23 15:16:03 2017 Matthias Prost
*/

#include "server.h"

t_commands g_commands [NBR_ARGS] = {
  {"-p", &portArg},
  {"-x", &widthArg},
  {"-y", &heightArg},
  {"-c", &clientsNbArg},
  {"-f", &freqArg},
  {"-n", &nameArg},
};

void		serverInit(t_env *env)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    env->users[i].socket = -1;
  memset(env->fd_type, FD_FREE, MAX_FD);
  createMap(env);
  createServer(env);
}

void  args(t_env *env, char **av)
{
  int   i;
  int   a;

  i = -1;
  while (av[++i])
  {
    a = -1;
    while (++a != NBR_ARGS)
      if (av[i] != NULL
          && strncmp(av[i], g_commands[a].command, strlen(av[i])) == 0)
      {
        g_commands[a].p(env, av, i);
        break;
      }
  }
  if (!(env->port) || !(env->width) || !(env->height) || !(env->clientsNb))
  {
    printf("ERROR: A value haven't been set, please look at the usage\n");
    printUsage();
    exit(EXIT_FAILURE);
  }
}

void		printUsage()
{
  printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2"
          " ... -c clientsNb -f freq\n\tport\t\t is the port number\n"
          "\twidth\t\t is the width of the world\n"
          "\theight\t\t is the height of the world\n"
          "\tnameX\t\t is the name of the team X\n"
          "\tclientsNb\t is the number of authorized clients per team\n"
          "\tfreq\t\t is the reciprocal of time unit for"
          "execution of actions\n");
  exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
  t_env		env;

  if (ac < 12 || strcmp(av[1], "-help") == 0)
    printUsage();
  srand(time(NULL));
  env.freq = 100;
  args(&env, av);
  serverInit(&env);
  serverLoop(&env);
  return (0);
}
