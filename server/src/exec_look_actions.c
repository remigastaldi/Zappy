/*
** exec_look_actions.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Wed Jun 28 16:56:20 2017 gastal_r
** Last update Wed Jun 28 19:01:05 2017 Leo Hubert Froideval
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

void          inventoryAction(t_env *env, char **msg, t_users *user)
{
  (void)env;
  (void)msg;
  dprintf(user->socket, "[linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d, food %d]\n",
   user->inventory.linemate,
   user->inventory.deraumere,
   user->inventory.sibur,
   user->inventory.mendiane,
   user->inventory.phiras,
   user->inventory.thystame,
   user->inventory.food);
}
