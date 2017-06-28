/*
** refresh_queue.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Wed Jun 28 14:46:13 2017 gastal_r
** Last update Wed Jun 28 16:40:11 2017 gastal_r
*/

#include      "utilities.h"
#include      "server.h"

void          refresh_queue(t_env *env)
{
  double      curr_clock;
  t_action    *action;
  t_action    *tmp;

  action = env->queue->head;
  curr_clock = clock() / CLOCKS_PER_SEC;
  while (action)
  {
    if (curr_clock >= action->time_limit)
    {
      tmp = action->next;
      (*action->p)(action->env, action->msg, action->user);
      deleteAction(env->queue, action);
      action = tmp;
    }
    if (action != NULL)
      action = action->next;
  }
}
