/*
** refresh_queue.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Wed Jun 28 14:46:13 2017 gastal_r
** Last update Sun Jul  2 14:35:42 2017 gastal_r
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
  while (action)
  {
    gettimeofday(&curr_time, NULL);
    curr_clock = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
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
  while (++i < 255)
  {
    gettimeofday(&curr_time, NULL);
    curr_clock = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
    if (env->users[i].teamName != NULL
      && curr_clock >= env->users[i].food_timer)
    {
      env->users[i].inventory.food--;
      respawn_ressources(env, "food");
      printf("Player %d have %d food left\n", env->users[i].socket,
        env->users[i].inventory.food);
      if (env->users[i].inventory.food == 0)
      {
        delete_all_player_actions(env, &env->users[i]);
        if (env->users[i].socket != -1)
        {
          dprintf(env->users[i].socket, "dead\n");
          printf("--> Sent: \"dead\" to socket %d\n", env->users[i].socket);
        }
        removeUserTab(env, env->users[i].socket);
      }
      else
        env->users[i].food_timer = curr_clock + (126000000 / env->freq);
    }
  }
}
