/*
** look.c for  in /home/puccio_c/rendu/PSU/Zappy/server/src
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Thu Jun 22 20:14:09 2017 Cyril Puccio
** Last update Thu Jun 22 20:14:15 2017 Cyril Puccioo
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
  int           i;
  char          *str;
  int           nb_item;
  t_items       tmp;

  str = strdup("");
  tmp = env->map[x][y];
  nb_item = tmp.linemate + tmp.deraumere + tmp.sibur;
  nb_item += tmp.mendiane + tmp.phiras + tmp.thystame;
  i = -1;
  while (++i != nb_item)
    {
      if (tmp.linemate-- > 0)
        str = my_strcat(str, "linemate");
      else if (tmp.deraumere-- > 0)
        str = my_strcat(str, "deraumere");
      else if (tmp.sibur-- > 0)
        str = my_strcat(str, "sibur");
      else if (tmp.mendiane-- > 0)
        str = my_strcat(str, "mendiane");
      else if (tmp.phiras-- > 0)
        str = my_strcat(str, "phiras");
      else if (tmp.thystame-- > 0)
        str = my_strcat(str, "thystame");
      (i + 1 != nb_item ? str = my_strcat(str, " ") : 0);
    }
  // (nb_item > 0 ? str = my_strcat(str, "\b\b]") : (str = my_strcat(str, "]")));
  printf("%s\n", str);
  return (str);
}

int             calc_pos(t_env *env, int *x, int *y, int lvl)
{
  if (env->users->direction == 0)
  {
    (*x) = (*x) - lvl;
    (*y) = (*y) - lvl;
    printf("calcx: %d calcy: %d\n", *x, *y);
  }
  return (0);
}

int             change_case(t_env *env, int *x, int *y)
{
  (void)y;
  if (env->users->direction == 0)
    (*x) = (*x) + 1;
  printf("changex: %d changey: %d\n", *x, *y);
  return (0);
}

char            *check_case(t_env *env, char *pos, int i)
{
  int           j;
  int           x;
  int           y;

  j = -1;
  x = env->users->posX;
  y = env->users->posY;
  printf("x: %d y: %d\n", x, y);
  calc_pos(env, &x, &y, i);
  while (++j != (i * 2 + 1))
  {
    change_case(env, &x, &y);
    pos = my_strcat(pos, ressource_to_string(env, x, y));
    pos = my_strcat(pos, ", ");
  }
  return (pos);
}

char            *final_output(t_env *env, int lvl)
{
  char          *pos;
  int           i;

  i = 0;
  pos = "";
  while (++i != lvl + 1)
    {
      pos = check_case(env, pos, i);

    }
  return (pos);
}

int             cmd_look(t_env *env)
{
  char          *tmp;
  char          *final = malloc (100);

  env->users->lvl = 2;
  env->users->direction = 0;
  env->users->posX = 5;
  env->users->posY = 5;
  printf("userlvl: %d\n", env->users->lvl);
  // printf("pos: x: %d y: %d\n", env->users->posX, env->users->posY);
  tmp = final_output(env, env->users->lvl);
  sprintf(final, "[%s]\n", tmp);
  printf("%s\n", final);
  // free(final);
  // free(tmp);
  return (0);
}
