/*
** workingQueueFunctions.c for Zappy
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Wed Jun 28 15:53:40 2017 Leo Hubert Froideval
** Last update Sun Jul  2 21:59:40 2017 Matthias Prost
*/

#include "server.h"

void		addActionData(t_action *action, t_env *env, char **msg)
{
  if (action)
    {
      action->msg = msg;
      action->env = env;
    }
}

void		delete_all_player_actions(t_env *env, t_users *player)
{
  t_action	*ptr;
  t_action	*tmp;

  if (env->queue == NULL)
    return;
  ptr = env->queue->head;
  while (ptr != NULL)
    {
      tmp = ptr->next;
      if (ptr->user == player && strcmp(ptr->msg[0], "Fork") != 0)
	{
	  printf("DELETE ACTION %s BY PLAYER\n", ptr->msg[0]);
	  deleteAction(env, env->queue, ptr);
	}
      ptr = tmp;
    }
}

void		delete_all_fd_actions(t_env *env, int socket)
{
  t_action	*ptr;
  t_action	*tmp;

  if (env->queue == NULL)
    return;
  ptr = env->queue->head;
  while (ptr != NULL)
    {
      tmp = ptr->next;
      if (ptr->user->socket == socket)
	{
	  printf("DELETE ACTION %s BY FD number %d\n", ptr->msg[0], socket);
	  deleteAction(env, env->queue, ptr);
	}
      ptr = tmp;
    }
}
