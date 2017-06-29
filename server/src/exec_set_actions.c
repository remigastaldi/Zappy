/*
** exec_objects_actions.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 29 15:33:56 2017 Matthias Prost
** Last update Thu Jun 29 15:34:02 2017 Matthias Prost
*/

#include "server.h"

int  setObjectLinDer(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (strcmp(msg[1], "linemate") == 0 && user->inventory.linemate > 0)
  {
    env->map[y][x].linemate += 1;
    user->inventory.linemate -= 1;
    printf("User with socket %d set a linemate\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  else if (strcmp(msg[1], "deraumere") == 0 && user->inventory.deraumere > 0)
  {
    env->map[y][x].deraumere += 1;
    user->inventory.deraumere -= 1;
    printf("User with socket %d set a deraumere\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

int  setObjectSibMen(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (strcmp(msg[1], "sibur") == 0 && user->inventory.sibur > 0)
  {
    env->map[y][x].sibur += 1;
    user->inventory.sibur -= 1;
    printf("User with socket %d set a sibur\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  else if (strcmp(msg[1], "mendiane") == 0 && user->inventory.mendiane > 0)
  {
    env->map[y][x].mendiane += 1;
    user->inventory.mendiane -= 1;
    printf("User with socket %d set a mendiane\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

int  setObjectPhiThy(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (strcmp(msg[1], "phiras") == 0 && user->inventory.phiras > 0)
  {
    env->map[y][x].phiras += 1;
    user->inventory.phiras -= 1;
    printf("User with socket %d set a phiras\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  else if (strcmp(msg[1], "thystame") == 0 && user->inventory.thystame > 0)
  {
    env->map[y][x].thystame += 1;
    user->inventory.thystame -= 1;
    printf("User with socket %d set a thystame\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

int  setObjectFood(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (strcmp(msg[1], "food") == 0 && user->inventory.food > 0)
  {
    env->map[y][x].food += 1;
    user->inventory.food -= 1;
    printf("User with socket %d set food\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

void  setAction(t_env *env, char **msg, t_users *user)
{
  if (setObjectLinDer(env, msg, user) == 0
      && setObjectSibMen(env, msg, user) == 0
        && setObjectPhiThy(env, msg, user) == 0
          && setObjectFood(env, msg, user) == 0)
  {
    dprintf(user->socket, "ko\n");
    printf("--> Sent: \"ko\" to socket %d\n", user->socket);
  }
}
