/*
** workingQueue.c for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/server/src
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Fri Jun 23 16:22:34 2017 Leo Hubert Froideval
** Last update Wed Jun 28 13:21:52 2017 gastal_r
*/

#include "server.h"

t_queue    *initWorkingQueue()
{
  t_queue  *queue;

  queue = xmalloc(sizeof(t_queue));
  queue->actions = 0;
  queue->head = NULL;
  queue->end = NULL;
  return (queue);
}

void        newAction(t_queue *queue, t_users *user, void *func, double ac_time)
{
  t_action  *newAction;

  newAction = xmalloc(sizeof(t_action));
  newAction->time_limit = clock() / CLOCKS_PER_SEC + ac_time;
  newAction->user = user;
  newAction->next = NULL;
  newAction->prev = NULL;
  newAction->p = func;
  queue->actions++;
  if (queue->head == NULL)
    queue->head = newAction;
  else
  {
    newAction->prev = queue->end;
    queue->end->next = newAction;
  }
  queue->end = newAction;
}

int         deleteAction(t_queue *queue, t_action *action)
{
  t_action  *ptr;

  if (queue == NULL)
    return (-1);
  ptr = queue->head;
  while (ptr != NULL)
  {
    if (ptr == action)
    {
      if (ptr->prev != NULL)
        ptr->prev->next = ptr->next;
      if (ptr->next != NULL)
        ptr->next->prev = ptr->prev;
      if (ptr == queue->head)
        queue->head = ptr->next;
      else if (ptr == queue->end)
        queue->end = ptr->prev;
      queue->actions--;
      free(ptr);
      return (1);
    }
    ptr = ptr->next;
  }
  return (0);
}

void      printWorkingQueue(t_queue *queue)
{
  t_action *ptr;

  ptr = queue->head;
  printf("Total actions in queue: %d\n", queue->actions);
  while (ptr != NULL)
  {
    ptr = ptr->next;
  }
}

void    freeWorkingQueue(t_queue *queue)
{
  t_action *ptr;
  t_action *savePtr;

  queue->actions = 0;
  ptr = queue->head;
  queue->head = NULL;
  queue->end = NULL;
  while (ptr != NULL)
  {
    savePtr = ptr->next;
    free(ptr);
    ptr = savePtr;
  }
  free(queue);
}
