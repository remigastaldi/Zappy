/*
** workingQueueFunctions.c for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/server/src
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Wed Jun 28 15:53:40 2017 Leo Hubert Froideval
** Last update Fri Jun 30 20:44:22 2017 gastal_r
*/

#include "server.h"

void    addActionData(t_action *action, t_env *env, char **msg)
{
  if (action)
  {
    action->msg = msg;
    action->env = env;
  }
}

void    delete_all_player_actions(t_env *env, t_users *player)
{
  t_action  *ptr;

  if (env->queue == NULL)
    return;
  ptr = env->queue->head;
  while (ptr != NULL)
  {
    if (ptr->user == player)
      deleteAction(env, env->queue, ptr);
  }
}
