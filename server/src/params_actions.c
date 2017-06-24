/*
** params_actions.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 23 15:43:06 2017 Matthias Prost
** Last update Sat Jun 24 17:04:06 2017 Matthias Prost
*/

#include "server.h"

void  forwardYMoving(t_env *env, t_users *user)
{
  if (user->direction == UP)
  {
    if (user->posY == 0)
      user->posY = env->height - 1;
    else
      user->posY = user->posY - 1;
    printf("User with socket %d moved UP on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
  else if (user->direction == DOWN)
  {
    if (user->posY == env->height - 1)
      user->posY = 0;
    else
      user->posY = user->posY + 1;
    printf("User with socket %d moved DOWN on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
}

void  forwardParam(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  forwardYMoving(env, user);
  if (user->direction == LEFT)
  {
    if (user->posX == 0)
      user->posX = env->width - 1;
    else
      user->posX = user->posX - 1;
    printf("User with socket %d moved LEFT on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
  else if (user->direction == RIGHT)
  {
    if (user->posX == env->width - 1)
      user->posX = 0;
    else
      user->posX = user->posX + 1;
    printf("User with socket %d moved RIGHT on position %dy : %dx\n",
          user->socket, user->posY, user->posX);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
}

void  rightParam(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  (void)env;
  user->direction = RIGHT;
  printf("User with socket %d turn 90 deg right\n", user->socket);
  dprintf(user->socket, "ok\n");
  printf("--> Sent: \"ok\" to socket %d\n", user->socket);
}

void  leftParam(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  (void)env;
  user->direction = LEFT;
  printf("User with socket %d turn 90 deg left\n", user->socket);
  dprintf(user->socket, "ok\n");
  printf("--> Sent: \"ok\" to socket %d\n", user->socket);
}