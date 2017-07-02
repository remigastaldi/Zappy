/*
** exec_actions.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Jun 28 15:32:09 2017 Matthias Prost
** Last update Wed Jun 28 15:32:09 2017 Matthias Prost
*/

#include "server.h"

void  forwardYMoving(t_env *env, t_users *user)
{
  if (user->socket != -1 && user->direction == UP)
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
  else if (user->direction == DOWN && user->socket != -1)
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

void  forwardAction(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  forwardYMoving(env, user);
  if (user->socket != -1 && user->direction == LEFT)
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
  else if (user->socket != -1 && user->direction == RIGHT)
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

void  rightAction(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  (void)env;
  if (user->socket != -1)
  {
    if (user->direction == UP)
      user->direction = RIGHT;
    else if (user->direction == RIGHT)
      user->direction = DOWN;
    else if (user->direction == DOWN)
      user->direction = LEFT;
    else if (user->direction == LEFT)
      user->direction = UP;
    printf("User with socket %d turn 90 deg right\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
}

void  leftAction(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  (void)env;
  if (user->socket != -1)
  {
    if (user->direction == UP)
      user->direction = LEFT;
    else if (user->direction == LEFT)
      user->direction = DOWN;
    else if (user->direction == DOWN)
      user->direction = RIGHT;
    else if (user->direction == RIGHT)
      user->direction = UP;
    printf("User with socket %d turn 90 deg left\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
}
