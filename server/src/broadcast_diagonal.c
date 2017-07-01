#include "server.h"

int         diagonal2(int x, int y, t_env *env)
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
    return (diagonal2(x, y, env));
  }
  return (0);
}
