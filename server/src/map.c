/*
** map.c for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/server/src
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Thu Jun 22 16:33:09 2017 Leo Hubert Froideval
** Last update Thu Jun 22 17:22:48 2017 Leo Hubert Froideval
*/


#include "server.h"

void    createMap(t_env *env)
{
  int   i;
  int   j;

  i = -1;
  env->map = xmalloc(sizeof(t_items *) * (env->height + 1));
  while (++i != env->height)
  {
    j = -1;
    env->map[i] = xmalloc(sizeof(t_items) * env->width);
    while(++j != env->width)
    {
      env->map[i][j].linemate = 12;
      env->map[i][j].deraumere = 0;
      env->map[i][j].sibur = 0;
      env->map[i][j].mendiane = 0;
      env->map[i][j].phiras = 0;
      env->map[i][j].thystame = 0;
    }
  }
  env->map[i] = NULL;
}
