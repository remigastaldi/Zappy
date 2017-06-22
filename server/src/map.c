/*
** map.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 22 17:41:34 2017 Matthias Prost
** Last update Thu Jun 22 17:41:38 2017 Matthias Prost
*/

#include "server.h"

void  fillRessourcesMap(t_env *env)
{
  int   i;

  (void)env;
  i = rand() % ((env->height * env->width) + 1
  - ((env->height * env->width) / 10)) + (env->height * env->width) / 10;
  env->nbrRessources = i;
}

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
      env->map[i][j].linemate = 0;
      env->map[i][j].deraumere = 0;
      env->map[i][j].sibur = 0;
      env->map[i][j].mendiane = 0;
      env->map[i][j].phiras = 0;
      env->map[i][j].thystame = 0;
    }
  }
  env->map[i] = NULL;
  fillRessourcesMap(env);
}
