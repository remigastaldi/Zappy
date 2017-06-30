/*
** params_actions.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 23 15:43:06 2017 Matthias Prost
** Last update Fri Jun 30 12:09:17 2017 gastal_r
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
  dprintf(user->socket, "ko\n");
  printf("--> Sent: \"ko\" to socket %d\n", user->socket);
  free_tab(msg);
}
