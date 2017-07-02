/*
** map.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 22 17:41:34 2017 Matthias Prost
** Last update Sun Jul  2 22:07:10 2017 Matthias Prost
*/

#include "server.h"

void		fillRessourcesMap(t_env *env)
{
  int		x;
  int		y;
  int		nbr;

  x = -1;
  y = -1;
  nbr = 0;
  while (++y != env->height)
    {
      while (++x != env->width)
	{
	  nbr += (env->map[y][x].linemate = rand() % LINEMATE);
	  nbr += (env->map[y][x].deraumere = rand() % DERAUMERE);
	  nbr += (env->map[y][x].sibur = rand() % SIBUR);
	  nbr += (env->map[y][x].mendiane = rand() % MENDIANA);
	  nbr += (env->map[y][x].phiras = rand() % PHIRAS);
	  nbr += (env->map[y][x].thystame = rand() % THYSTAME);
	  nbr += (env->map[y][x].food = rand() % FOOD);
	  nbr += (env->map[y][x].egg = 0);
	}
      x = -1;
    }
  env->nbrRessources = nbr;
}

void		createMap(t_env *env)
{
  int		i;
  int		j;

  i = -1;
  env->map = xmalloc(sizeof(t_items *) * (env->height + 1));
  while (++i != env->height)
    {
      j = -1;
      env->map[i] = xmalloc(sizeof(t_items) * env->width);
      while (++j != env->width)
	{
	  env->map[i][j].linemate = 0;
	  env->map[i][j].deraumere = 0;
	  env->map[i][j].sibur = 0;
	  env->map[i][j].mendiane = 0;
	  env->map[i][j].phiras = 0;
	  env->map[i][j].thystame = 0;
	  env->map[i][j].food = 0;
	  env->map[i][j].egg = 0;
	}
    }
  env->map[i] = NULL;
  fillRessourcesMap(env);
}
