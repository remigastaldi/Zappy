/*
** exec_look_actions.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Wed Jun 28 16:56:20 2017 gastal_r
** Last update Thu Jun 29 18:07:35 2017 gastal_r
*/

#include      "server.h"


void          lookParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &lookAction, 7000000 / env->freq);
  addActionData(action, env, msg);
}

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

  dprintf(user->socket, "linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d, food %d\n",
   user->inventory.linemate,
   user->inventory.deraumere,
   user->inventory.sibur,
   user->inventory.mendiane,
   user->inventory.phiras,
   user->inventory.thystame,
   user->inventory.food);
}
