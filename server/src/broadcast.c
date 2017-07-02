/*
** brodcast.c for  in /home/puccio_c/rendu/PSU/Zappy
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Fri Jun 30 15:10:54 2017 Cyril Puccio
** Last update Sun Jul  2 21:38:19 2017 Matthias Prost
*/

#include "server.h"

int		find_case_vert(t_users *ur, int dir)
{
  if (ur->direction == UP)
    {
      return ((dir == 1 ? 7 :
	       dir == 2 ? 8 :
	       dir == 3 ? 1 :
	       dir == 4 ? 2 :
	       dir == 5 ? 3 :
	       dir == 6 ? 4 :
	       dir == 7 ? 5 :
	       dir == 8 ? 6 : 0));
    }
  if (ur->direction == DOWN)
    {
      return ((dir == 1 ? 3 :
	       dir == 2 ? 4 :
	       dir == 3 ? 5 :
	       dir == 4 ? 6 :
	       dir == 5 ? 7 :
	       dir == 6 ? 8 :
	       dir == 7 ? 1 :
	       dir == 8 ? 2 : 0));
    }
  return (dir);
}

int		is_cardinal(t_users *us, t_users *ur)
{
  if ((us->posX == ur->posX) && (us->posY == ur->posY))
    return (0);
  else if ((us->posX == ur->posX) || (us->posY == ur->posY))
    {
      if (us->posX == ur->posX)
        return (1);
      if (us->posY == ur->posY)
        return (2);
    }
  return (-1);
}

int		handle_cardinal(t_env *env, int y)
{
  if (y > 0)
    if (y > (env->height / 2))
      return (3);
    else
      return (7);
  else
    if (y * (-1) > (env->height / 2))
      return (7);
    else
      return (3);
}

int		cartdinal(t_users *us, t_users *ur, t_env *env)
{
  int		x;
  int		y;

  x = us->posX - ur->posX;
  y = us->posY - ur->posY;
  if (is_cardinal(us, ur) == 2)
    {
      if (x > 0)
	if (x > (env->width / 2))
	  return (5);
	else
	  return (1);
      else
	if (x * (-1) > (env->width / 2))
	  return (1);
	else
	  return (5);
    }
  else if (is_cardinal(us, ur) == 1)
    {
      return (handle_cardinal(env, y));
    }
  return (0);
}

int		broadcast(t_users *us, t_users *ur, t_env *env)
{
  int		dir;
  int		fin_dir;

  if (is_cardinal(us, ur) >= 0)
    dir = cartdinal(us, ur, env);
  else
    dir = diagonal(us, ur, env);
  fin_dir = find_case_hor(ur, dir);
  if (fin_dir == dir)
    fin_dir = find_case_vert(ur, dir);
  printf("dir: %d\n", fin_dir);
  return (fin_dir);
}
