/*
** workingQueue.c for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/server/src
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Fri Jun 23 16:22:34 2017 Leo Hubert Froideval
** Last update Fri Jun 23 17:05:19 2017 Leo Hubert Froideval
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

void        newAction(t_queue *queue, t_users *user, enum Action action, int time)
{
  t_action  *newAction;

  newAction = xmalloc(sizeof(t_action));
  newAction->time = time;
  newAction->action = action;
  newAction->user = user;
  newAction->next = NULL;
  queue->actions++;
  if (queue->head == NULL)
    queue->head = newAction;
  else
    queue->end->next = newAction;
  queue->end = newAction;
}

void      printWorkingQueue(t_queue *queue)
{
  t_action *ptr;

  ptr = queue->head;
  printf("Total actions in queue: %d\n", queue->actions);
  while (ptr != NULL)
  {
    printf("Time: %d; Action: %d\n", ptr->time, ptr->action);
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
