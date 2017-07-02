/*
** params_actions.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 23 15:43:06 2017 Matthias Prost
** Last update Sun Jul  2 13:26:08 2017 Matthias Prost
*/

#include "server.h"

void  forwardParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &forwardAction, 7000000 / env->freq);
  addActionData(action, env, msg);
}

void  rightParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &rightAction, 7000000 / env->freq);
  addActionData(action, env, msg);
}

void  leftParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &leftAction, 7000000 / env->freq);
  addActionData(action, env, msg);
}

void  inventoryParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &inventoryAction, 1000000 / env->freq);
  addActionData(action, env, msg);
}

void  koParam(t_env *env, char **msg, t_users *user)
{
  (void)env;
  (void)msg;
  if (user->socket != -1)
  {
    dprintf(user->socket, "ko\n");
    printf("--> Sent: \"ko\" to socket %d\n", user->socket);
  }
  free_tab(msg);
}
