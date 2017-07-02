/*
** user_distance.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Sun Jul  2 22:36:51 2017 Matthias Prost
** Last update Sun Jul  2 22:36:51 2017 Matthias Prost
*/

#include "server.h"

double		distance_users(t_users *userA, t_users *userB)
{
  double	distance;

  distance = sqrt((pow(((double)userB->posX - (double)userA->posX), 2)
		   + pow(((double)userB->posY - (double)userA->posY), 2)));
  return (distance);
}

void		fill_distance(t_distance *user_distance)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    {
      user_distance[i].distance = -1;
      user_distance[i].user = NULL;
    }
}
