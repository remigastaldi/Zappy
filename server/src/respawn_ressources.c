/*
** respaw,_ressources.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Sun Jul  2 14:36:43 2017 Matthias Prost
** Last update Sun Jul  2 20:38:43 2017 gastal_r
*/

#include "server.h"

void    respawn_ressources(t_env *env, char *ressource)
{
  int   x;
  int   y;

  x = rand() % env->width;
  y = rand() % env->height;
  if (strcmp(ressource, "linemate") == 0)
    env->map[y][x].linemate += 1;
  if (strcmp(ressource, "deraumere") == 0)
    env->map[y][x].deraumere += 1;
  if (strcmp(ressource, "sibur") == 0)
    env->map[y][x].sibur += 1;
  if (strcmp(ressource, "mendiane") == 0)
    env->map[y][x].mendiane += 1;
  if (strcmp(ressource, "phiras") == 0)
    env->map[y][x].phiras += 1;
  if (strcmp(ressource, "thystame") == 0)
    env->map[y][x].thystame += 1;
  if (strcmp(ressource, "food") == 0)
  {
    if (env->map[y][x].food > 10)
      return (respawn_ressources(env, "food"));
    env->map[y][x].food += 1;
  }
}
