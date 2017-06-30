/*
** refresh_queue.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Wed Jun 28 14:46:13 2017 gastal_r
** Last update Fri Jun 30 21:01:14 2017 gastal_r
*/

#include      "utilities.h"
#include      "server.h"

void          refresh_queue(t_env *env)
{
  struct      timeval curr_time;
  long  long  curr_clock;
  t_action    *action;
  t_action    *tmp;


  action = env->queue->head;
  gettimeofday(&curr_time, NULL);
  curr_clock = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
  while (action)
  {
    if (curr_clock >= action->time_limit)
    {
      tmp = action->next;
      (*action->p)(action->env, action->msg, action->user);
      deleteAction(env, env->queue, action);
      action = tmp;
    }
    if (action != NULL)
      action = action->next;
  }
}

void           refresh_player_food(t_env *env)
{
  struct      timeval curr_time;
  long  long  curr_clock;
  int         i;

  i = -1;
  gettimeofday(&curr_time, NULL);
  curr_clock = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
  while (++i < 255)
  {
    if (env->users[i].teamName != NULL
      && curr_clock >= env->users[i].food_timer)
    {
      env->users[i].inventory.food--;
      printf("Player %d have %d food left\n", env->users[i].socket,
        env->users[i].inventory.food);
      if (env->users[i].inventory.food == 0)
      {
        delete_all_player_actions(env, &env->users[i]);
        dprintf(env->users[i].socket, "dead");
        removeUserTab(env, env->users[i].socket);
      }
      else
        env->users[i].food_timer = curr_clock + (12600000 / env->freq);
    }
  }
}
