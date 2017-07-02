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

int  takeObjectLinDer(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (user->socket != -1 && strcmp(msg[1], "linemate") == 0
      && env->map[y][x].linemate > 0)
  {
    env->map[y][x].linemate -= 1;
    user->inventory.linemate += 1;
    printf("User with socket %d take a linemate\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  else if (user->socket != -1 && strcmp(msg[1], "deraumere") == 0
            && env->map[y][x].deraumere > 0)
  {
    env->map[y][x].deraumere -= 1;
    user->inventory.deraumere += 1;
    printf("User with socket %d take a deraumere\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

int  takeObjectSibMen(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (user->socket != -1 && strcmp(msg[1], "sibur") == 0
        && env->map[y][x].sibur > 0)
  {
    env->map[y][x].sibur -= 1;
    user->inventory.sibur += 1;
    printf("User with socket %d take a sibur\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  else if (user->socket != -1 && strcmp(msg[1], "mendiane") == 0
            && env->map[y][x].mendiane > 0)
  {
    env->map[y][x].mendiane -= 1;
    user->inventory.mendiane += 1;
    printf("User with socket %d take a mendiane\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

int  takeObjectPhiThy(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (user->socket != -1 && strcmp(msg[1], "phiras") == 0
      && env->map[y][x].phiras > 0)
  {
    env->map[y][x].phiras -= 1;
    user->inventory.phiras += 1;
    printf("User with socket %d take a phiras\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  else if (user->socket != -1 && strcmp(msg[1], "thystame") == 0
            && env->map[y][x].thystame > 0)
  {
    env->map[y][x].thystame -= 1;
    user->inventory.thystame += 1;
    printf("User with socket %d take a thystame\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

int  takeObjectFood(t_env *env, char **msg, t_users *user)
{
  int   x;
  int   y;

  x = user->posX;
  y = user->posY;
  if (user->socket != -1 && strcmp(msg[1], "food") == 0
      && env->map[y][x].food > 0)
  {
    env->map[y][x].food -= 1;
    user->inventory.food += 1;
    printf("User with socket %d take food\n", user->socket);
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    return (1);
  }
  return (0);
}

void  takeAction(t_env *env, char **msg, t_users *user)
{
  if (user->socket != -1 && takeObjectLinDer(env, msg, user) == 0
      && takeObjectSibMen(env, msg, user) == 0
        && takeObjectPhiThy(env, msg, user) == 0
          && takeObjectFood(env, msg, user) == 0)
  {
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
    // dprintf(user->socket, "ko\n");
    // printf("--> Sent: \"ko\" to socket %d\n", user->socket);
  }
}
