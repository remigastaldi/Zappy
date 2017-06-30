/*
** params_broadcast.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 30 16:21:34 2017 Matthias Prost
** Last update Fri Jun 30 16:22:05 2017 Matthias Prost
*/

#include "server.h"

void  broadcastParam(t_env *env, char **msg, t_users *user)
{
  t_action *action;
  action = newAction(env->queue, user, &broadcastAction, 7000000 / env->freq);
  addActionData(action, env, msg);
}
