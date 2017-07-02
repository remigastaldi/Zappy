/*
** look.c for  in /home/puccio_c/rendu/PSU/Zappy/server/src
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Thu Jun 22 20:14:09 2017 Cyril Puccio
** Last update Sun Jul  2 21:49:18 2017 Matthias Prost
*/

#include "server.h"

int		calc_pos(t_env *env, int *x, int *y, int lvl)
{
  if (env->users->direction == 0)
    {
      (*x) = (*x) - lvl;
      (*y) = (*y) - lvl;
    }
  if (env->users->direction == 1)
    {
      (*x) = (*x) + lvl;
      (*y) = (*y) + lvl;
    }
  if (env->users->direction == 2)
    {
      (*x) = (*x) + lvl;
      (*y) = (*y) - lvl;
    }
  if (env->users->direction == 3)
    {
      (*x) = (*x) - lvl;
      (*y) = (*y) + lvl;
    }
  ((*x) < 0 ? (*x) += env->width : 0);
  ((*y) < 0 ? (*y) += env->height : 0);
  ((*x) > env->width - 1 ? (*x) -= env->width : 0);
  ((*y) > env->height - 1 ? (*y) -= env->height : 0);
  return (0);
}

int		change_case(t_env *env, int *x, int *y)
{
  if (env->users->direction == 0)
    (*x) = (*x) + 1;
  if (env->users->direction == 1)
    (*x) = (*x) - 1;
  if (env->users->direction == 2)
    (*y) = (*y) + 1;
  if (env->users->direction == 3)
    (*y) = (*y) - 1;
  ((*x) < 0 ? (*x) += env->width : 0);
  ((*y) < 0 ? (*y) += env->height : 0);
  ((*x) > env->width - 1 ? (*x) -= env->width : 0);
  ((*y) > env->height - 1 ? (*y) -= env->height : 0);
  return (0);
}

char		*check_case(t_env *env, t_users *user, char *pos, int i)
{
  int		j;
  int		x;
  int		y;
  char		*res;

  j = -1;
  x = user->posX;
  y = user->posY;
  printf("x: %d y: %d\n", x, y);
  if ((res = ressource_to_string(env, user, x, y)) != NULL)
    pos = my_strcat(pos, res, -1, -1);
  res != NULL ? free(res) : 0;
  pos = my_strcat(pos, ",", -1, -1);
  calc_pos(env, &x, &y, i);
  while (++j != (i * 2 + 1))
    {
      if ((res = ressource_to_string(env, user, x, y)) != NULL)
        pos = my_strcat(pos, ressource_to_string(env, user, x, y), -1, -1);
      res != NULL ? free(res) : 0;
      pos = my_strcat(pos, ",", -1, -1);
      change_case(env, &x, &y);
    }
  pos = my_strcat(pos, "\0", -1, -1);
  return (pos);
}

char		*final_output(t_env *env, t_users *user, int lvl)
{
  char		*pos;
  int		i;

  i = 0;
  pos = NULL;
  while (++i != lvl + 1)
    {
      pos = check_case(env, user, pos, i);
    }
  return (pos);
}

char		*cmd_look(t_env *env, t_users *user)
{
  char		*final;

  final = final_output(env, user, user->lvl);
  printf("%s\n", final);
  return (final);
}
