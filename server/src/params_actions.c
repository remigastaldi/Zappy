/*
** params_actions.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 23 15:43:06 2017 Matthias Prost
** Last update Sat Jun 24 16:43:35 2017 Matthias Prost
*/

#include "server.h"

void  forwardParam(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  if (user->direction == UP)
  {
    if (user->posY == 0)
      user->posY = env->height - 1;
    else
      user->posY = user->posY - 1;
    printf("User with socket %d go UP on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
  }
  else if (user->direction == DOWN)
  {
    if (user->posY == env->height - 1)
      user->posY = 0;
    else
      user->posY = user->posY + 1;
    printf("User with socket %d go DOWN on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
  }
  else if (user->direction == LEFT)
  {
    if (user->posX == 0)
      user->posX = env->width - 1;
    else
      user->posX = user->posX - 1;
    printf("User with socket %d go LEFT on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
  }
  else if (user->direction == RIGHT)
  {
    if (user->posX == env->width - 1)
      user->posX = 0;
    else
      user->posX = user->posX + 1;
    printf("User with socket %d go RIGHT on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
  }
}

void  rightParam(t_env *env, char **msg, t_users *user)
{
  printf("DONE\n");
  (void)env;
  (void)msg;
  (void)user;
}

void  leftParam(t_env *env, char **msg, t_users *user)
{
  printf("DONE\n");
  (void)env;
  (void)msg;
  (void)user;
}
