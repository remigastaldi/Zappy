/*
** broadcast_diagonal.c for  in /home/puccio_c/rendu/PSU/Zappy
** 
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
** 
** Started on  Sun Jul  2 14:11:39 2017 Cyril Puccio
** Last update Sun Jul  2 21:38:53 2017 Matthias Prost
*/

#include "server.h"

int		find_case_hor(t_users *ur, int dir)
{
  if (ur->direction == RIGHT)
    return (dir);
  if (ur->direction == LEFT)
    {
      return ((dir == 1 ? 5 :
	       dir == 2 ? 6 :
	       dir == 3 ? 7 :
	       dir == 4 ? 8 :
	       dir == 5 ? 1 :
	       dir == 6 ? 2 :
	       dir == 7 ? 3 :
	       dir == 8 ? 4 : 0));
    }
  return (dir);
}

int		diagonal2(int x, int y, t_env *env)
{
  if (y > 0)
    if (x * (-1) > (env->width / 2) || y * (-1) > (env->height / 2))
      return (2);
    else
      return (6);
  else
    if (x * (-1) > (env->width / 2) || y * (-1) > (env->height / 2))
      return (8);
    else
      return (4);
}

int		diagonal(t_users *us, t_users *ur, t_env *env)
{
  int		x;
  int		y;

  x = us->posX - ur->posX;
  y = us->posY - ur->posY;
  printf("x: %d y: %d\n", x, y);
  if (x > 0)
    {
      if (y > 0)
	if (x > (env->width / 2) || y > (env->height / 2))
	  return (4);
	else
	  return (8);
      else
	if (x > (env->width / 2) || y > (env->height / 2))
	  return (6);
	else
	  return (2);
    }
  else if (x < 0)
    {
      return (diagonal2(x, y, env));
    }
  return (0);
}
