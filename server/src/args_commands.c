/*
** args_commands.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 19:06:41 2017 Matthias Prost
** Last update	Thu Jun 15 19:52:55 2017 Full Name
*/

#include "server.h"

void   portArg(t_env *env, char **av, int i)
{
  int   a;

  a = -1;
  while (av[i + 1][++a])
  {
    if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
    {
      printf("ERROR: The port must be a positive number\n");
      exit(EXIT_FAILURE);
    }
  }
  env->port = atoi(av[i + 1]);
}

void   widthArg(t_env *env, char **av, int i)
{
  int   a;

  a = -1;
  while (av[i + 1][++a])
  {
    if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
    {
      printf("ERROR: The width must be a positive number\n");
      exit(EXIT_FAILURE);
    }
  }
  env->width = atoi(av[i + 1]);
}

void   heightArg(t_env *env, char **av, int i)
{
  int   a;

  a = -1;
  while (av[i + 1][++a])
  {
    if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
    {
      printf("ERROR: The height must be a positive number\n");
      exit(EXIT_FAILURE);
    }
  }
  env->height = atoi(av[i + 1]);
}

void    clientsNbArg(t_env *env, char **av, int i)
{
  int   a;

  a = -1;
  while (av[i + 1][++a])
  {
    if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
    {
      printf("ERROR: The number of client per team "
              "must be a positive number >= 6\n");
      exit(EXIT_FAILURE);
    }
  }
  if (atoi(av[i + 1]) < 6)
  {
    printf("ERROR: The number of client per team "
            "must be a positive number >= 6\n");
    exit(EXIT_FAILURE);
  }
  env->clientsNb = atoi(av[i + 1]);
}

void    freqArg(t_env *env, char **av, int i)
{
  int   a;

  a = -1;
  while (av[i + 1][++a])
  {
    if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
    {
      printf("ERROR: The fequency must be a positive number\n");
      exit(EXIT_FAILURE);
    }
  }
  env->freq = atoi(av[i + 1]);
}
