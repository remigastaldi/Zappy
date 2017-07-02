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

void		portArg(t_env *env, char **av, int i)
{
  int		a;

  a = -1;
  if (av[i + 1])
    {
      while (av[i + 1][++a])
	{
	  if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
	    print_error("ERROR: The port must be a positive number");
	}
      env->port = atoi(av[i + 1]);
    }
  else
    print_error("ERROR: The port must be a positive number");
}

void		widthArg(t_env *env, char **av, int i)
{
  int		a;

  a = -1;
  if (av[i + 1])
    {
      while (av[i + 1][++a])
	{
	  if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
	    print_error("ERROR: The width must be a positive number >= 10");
	}
      if (atoi(av[i + 1]) >= 10)
	env->width = atoi(av[i + 1]);
      else
	print_error("ERROR: The width must be a positive number >= 10");
    }
  else
    print_error("ERROR: The width must be a positive number >= 10");
}

void		heightArg(t_env *env, char **av, int i)
{
  int		a;

  a = -1;
  if (av[i + 1])
    {
      while (av[i + 1][++a])
	{
	  if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
	    print_error("ERROR: The height must be a positive number >= 10");
	}
      if (atoi(av[i + 1]) >= 10)
	env->height = atoi(av[i + 1]);
      else
	print_error("ERROR: The height must be a positive number >= 10");
    }
  else
    print_error("ERROR: The height must be a positive number >= 10");
}

void		clientsNbArg(t_env *env, char **av, int i)
{
  int		a;

  a = -1;
  if (av[i + 1])
    {
      while (av[i + 1][++a])
	{
	  if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
	    print_error("ERROR: The number of client per team "
			"must be a positive number >= 6");
	}
      env->clientsNb = atoi(av[i + 1]);
    }
  else
    print_error("ERROR: The number of client per team "
		"must be a positive number >= 6");
}

void		freqArg(t_env *env, char **av, int i)
{
  int		a;

  a = -1;
  if (av[i + 1])
    {
      while (av[i + 1][++a])
	{
	  if (av[i + 1][a] > '9' || av[i + 1][a] < '0')
	    print_error("ERROR: The fequency must be a positive number");
	}
      env->freq = atoi(av[i + 1]);
    }
  else
    print_error("ERROR: The fequency must be a positive number");
}
