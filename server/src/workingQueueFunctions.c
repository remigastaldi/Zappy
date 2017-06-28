/*
** workingQueueFunctions.c for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/server/src
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Wed Jun 28 15:53:40 2017 Leo Hubert Froideval
** Last update Wed Jun 28 16:15:01 2017 Matthias Prost
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
