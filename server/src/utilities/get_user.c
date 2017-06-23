/*
** get_user.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/utilities/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 23 15:51:02 2017 Matthias Prost
** Last update Fri Jun 23 17:12:43 2017 Matthias Prost
*/

#include "utilities.h"

void   get_user(t_env *env, int fd, t_users *user)
{
  int   i;

  i = -1;
  while (++i != MAX_FD)
    if (env->users[i].socket == fd)
      *user = env->users[i];
}
