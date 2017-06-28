/*
** params_client.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Jun 28 12:56:14 2017 Matthias Prost
** Last update Wed Jun 28 12:56:14 2017 Matthias Prost
*/

#include "server.h"

void  connect_nbrParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &connect_nbrAction, 0);
  addActionData(action, env, msg);
}
