/*
** exec_look_actions.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Wed Jun 28 16:56:20 2017 gastal_r
** Last update Wed Jun 28 18:03:43 2017 gastal_r
*/

#include      "server.h"

void          lookAction(t_env *env, char **msg, t_users *user)
{
  char  *look;

  (void)msg;
  look = cmd_look(env);
  dprintf(user->socket, "%s\n", look);
  free(look);
}
