/*
** exec_incantation_action.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 29 18:06:12 2017 Matthias Prost
** Last update Fri Jun 30 15:10:02 2017 Matthias Prost
*/

#include "server.h"

void  incantationAction(t_env *env, char **msg, t_users *user)
{
  (void)env;
  (void)msg;
  user->lvl += 1;
  dprintf(user->socket, "Current level: %d\n", user->lvl);
  printf("User with socket %d level up to %d\n", user->socket, user->lvl);
  printf("--> Sent \"Current level: %d\" to socket %d\n",
          user->lvl, user->socket);
}

void  forkAction(t_env *env, char **msg, t_users *user)
{
  (void)env;
  (void)msg;
  env->map[user->posY][user->posX].egg += 1;
  dprintf(user->socket, "ok\n");
  printf("--> Sent \"ok\" to socket %d\n", user->socket);
}
