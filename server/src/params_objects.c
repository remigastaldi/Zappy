/*
** params_objects.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 29 15:31:59 2017 Matthias Prost
** Last update Thu Jun 29 15:31:59 2017 Matthias Prost
*/

#include "server.h"

void  takeParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &takeAction, 7 / env->freq);
  addActionData(action, env, msg);
}
