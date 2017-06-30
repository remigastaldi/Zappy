/*
** look.c for  in /home/puccio_c/rendu/PSU/Zappy/server/src
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Thu Jun 22 20:14:09 2017 Cyril Puccio
** Last update Fri Jun 30 12:03:14 2017 gastal_r
*/

#include "server.h"

int             get_number_of_visible_space(int level)
{
  int           nb;

  nb = 1;
  while (level >= 1)
    {
      nb += ((level * 2) + 1);
      level--;
    }
  return (nb);
}

char            *ressource_to_string(t_env *env, int x, int y)
{
  char          *str;
  int           nb_item;
  t_items       tmp;

  str = NULL;
  tmp = env->map[y][x];
  nb_item = tmp.linemate + tmp.deraumere + tmp.sibur + tmp.food;
  nb_item += tmp.mendiane + tmp.phiras + tmp.thystame;
  while (nb_item-- != 0)
    {
      if (tmp.linemate-- > 0)
        str = my_strcat(str, "linemate", -1, -1);
      else if (tmp.deraumere-- > 0)
        str = my_strcat(str, "deraumere", -1, -1);
      else if (tmp.sibur-- > 0)
        str = my_strcat(str, "sibur", -1, -1);
      else if (tmp.mendiane-- > 0)
        str = my_strcat(str, "mendiane", -1, -1);
      else if (tmp.phiras-- > 0)
        str = my_strcat(str, "phiras", -1, -1);
      else if (tmp.thystame-- > 0)
        str = my_strcat(str, "thystame", -1, -1);
      else if (tmp.food-- > 0)
        str = my_strcat(str, "food", -1, -1);
      (nb_item  != 0 ? str = my_strcat(str, " ", -1, -1) : 0);
    }
    // printf("return==> %s\n", str);
  return (str);
}

int             calc_pos(t_env *env, int *x, int *y, int lvl)
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
  // printf("calc: %d calc: %d\n", *x, *y);
  return (0);
}

int             change_case(t_env *env, int *x, int *y)
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
  // printf("changex: %d changey: %d\n", *x, *y);
  return (0);
}

char            *check_case(t_env *env, char *pos, int i)
{
  int           j;
  int           x;
  int           y;
  char          *res;

  j = -1;
  x = env->users->posX;
  y = env->users->posY;
  printf("x: %d y: %d\n", x, y);
  if ((res = ressource_to_string(env, x, y)) != NULL)
    pos = my_strcat(pos, res, -1, -1);
  res != NULL ? free(res) : 0;
  pos = my_strcat(pos, ",", -1, -1);
  calc_pos(env, &x, &y, i);
  while (++j != (i * 2 + 1) - 1)
    {
      if ((res = ressource_to_string(env, x, y)) != NULL)
        pos = my_strcat(pos, ressource_to_string(env, x, y), -1, -1);
      res != NULL ? free(res) : 0;
      pos = my_strcat(pos, ",", -1, -1);
      change_case(env, &x, &y);
    }
  pos = my_strcat(pos, "\0", -1, -1);
  return (pos);
}

char            *final_output(t_env *env, int lvl)
{
  char          *pos;
  int           i;

  i = 0;
  pos = NULL;
  while (++i != lvl + 1)
    {
      pos = check_case(env, pos, i);

    }
  return (pos);
}

char            *cmd_look(t_env *env)
{
  char          *final;

  final = final_output(env, env->users->lvl);
  printf("%s\n", final);
  return (final);
}
