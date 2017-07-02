/*
** name_command.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Jun 21 13:44:40 2017 Matthias Prost
** Last update Sun Jul  2 21:52:14 2017 Matthias Prost
*/

#include "server.h"

void		nameArg(t_env *env, char **av, int i)
{
  int		a;
  int		buff;
  int		counter;

  buff = i;
  counter = 0;
  while (av[++i] && av[i][0] != '-')
    counter++;
  env->names = xmalloc(sizeof(char *) * (counter + 1));
  i = buff;
  a = -1;
  while (++a != counter)
    env->names[a] = strdup(av[++i]);
  env->names[a] = NULL;
}
