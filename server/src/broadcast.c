/*
** brodcast.c for  in /home/puccio_c/rendu/PSU/Zappy
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Fri Jun 30 15:10:54 2017 Cyril Puccio
** Last update Fri Jun 30 15:10:55 2017 Cyril Puccio
*/

#include "server.h"

int         find_case_hor(t_users *ur, int dir)
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

int         find_case_vert(t_users *ur, int dir)
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

int         is_cardinal(t_users *us, t_users *ur)
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

int         cartdinal(t_users *us, t_users *ur, t_env *env)
{
  int       x;
  int       y;

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
  return (0);
}

int         diagonal(t_users *us, t_users *ur, t_env *env)
{
  int       x;
  int       y;

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
  return (0);
}

int         broadcast(t_users *us, t_users *ur, t_env *env)
{
  int       dir;

  dir = 0;
  us->posX = 2;
  us->posY = 9;
  ur->posX = 9;
  ur->posY = 2;
  us->direction = 0;
  ur->direction = 2;
  if (is_cardinal(us, ur) >= 0)
    dir = cartdinal(us, ur, env);
  else
    dir = diagonal(us, ur, env);
  printf("dir: %d\n", dir);
  return (0);
}
