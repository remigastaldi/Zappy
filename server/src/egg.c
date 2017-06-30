/*
** egg.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Fri Jun 30 13:25:04 2017 gastal_r
** Last update Fri Jun 30 18:19:02 2017 gastal_r
*/

#include      "utilities.h"

void          add_opened_egg(t_env *env, int x, int y)
{
  t_egg       *egg;
  t_egg       *tmp;

  egg = xmalloc(sizeof(t_egg));
  egg->x = x;
  egg->y = y;
  egg->next = NULL;
  if (env->egg == NULL)
    env->egg = egg;
  else
  {
    tmp = env->egg;
    while (tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = egg;
  }
}

void          delete_front_egg(t_env *env)
{
  t_egg       *tmp;

  if (env->egg == NULL)
    return;
  tmp = env->egg->next;
  free(env->egg);
  env->egg = tmp;
}
