/*
** exec_broadcast_action.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 30 16:23:06 2017 Matthias Prost
** Last update Fri Jun 30 16:25:24 2017 Matthias Prost
*/

#include "server.h"

void  broadcastAction(t_env *env, char **msg, t_users *user)
{
  (void)env;
  (void)msg;
  dprintf(user->socket, "ok\n");
  printf("--> Sent: \"ok\" to socket %d\n", user->socket);
}
