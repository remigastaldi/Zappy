/*
** get_user.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/utilities/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 23 15:51:02 2017 Matthias Prost
** Last update Thu Jun 29 15:18:09 2017 Matthias Prost
*/

#include "utilities.h"

t_users   *get_user(t_env *env, int fd)
{
  int   i;

  i = -1;
  while (++i != MAX_FD)
    if (env->users[i].socket == fd)
      return(&env->users[i]);
  return (NULL);
}
