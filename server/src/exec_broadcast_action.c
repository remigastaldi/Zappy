/*
** exec_broadcast_action.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 30 16:23:06 2017 Matthias Prost
** Last update Sat Jul  1 15:23:47 2017 Matthias Prost
*/

#include "server.h"

double   distance_users(t_users *userA, t_users *userB)
{
  double  distance;

  distance = sqrt((pow(((double)userB->posX - (double)userA->posX), 2)
  + pow(((double)userB->posY - (double)userA->posY), 2)));
  return (distance);
}

void      fill_distance(t_distance *user_distance)
{
  int   i;

  i = -1;
  while (++i != MAX_FD)
  {
    user_distance[i].distance = -1;
    user_distance[i].user = NULL;
  }
}

void      bubble_sort(t_distance *user_distance, t_users *user, t_env *env)
{
  int        i;
  double     buffer;
  t_distance *user_dest;

  i = -1;
  user_dest = NULL;
  buffer = 1000;
  (void)user;
  while (++i != MAX_FD)
  {
    if (user_distance[i].user != NULL && user_distance[i].distance != -1
      && user_distance[i].user->socket != user->socket &&
      user_distance[i].distance < buffer)
    {
      buffer = user_distance[i].distance;
      user_dest = &user_distance[i];
    }
  }
  if (user_dest != NULL)
    {
      dprintf(user_dest->user->socket, "message %d\n",
              broadcast(user, user_dest->user, env));
      printf("--> Sent: \"message %d\" to socket%d\n", user_dest->user->socket,
              broadcast(user, user_dest->user, env));
      user_dest->user = NULL;
      user_dest->distance = -1;
    }
}

void      broadcastAction(t_env *env, char **msg, t_users *user)
{
  int       i;
  int       a;
  t_distance  user_distance[MAX_FD];

  (void)msg;
  i = -1;
  a = 0;
  fill_distance(&user_distance[0]);
  while (++i != MAX_FD)
  {
    if (env->users[i].socket != -1 && env->users[i].socket != user->socket &&
        strcmp(env->users[i].teamName, user->teamName) == 0
          && env->users[i].lvl == user->lvl)
          {
            printf("Distance between socket %d and socket %d: %lf\n",
              user->socket, env->users[i].socket,
                distance_users(user, &env->users[i]));
            user_distance[a].user = &env->users[i];
            user_distance[a].distance = distance_users(user, &env->users[i]);
            a++;
          }
  }
  a = -1;
  while (++a != user->lvl)
    bubble_sort(&user_distance[0], user, env);
  dprintf(user->socket, "ok\n");
  printf("--> Sent: \"ok\" to socket %d\n", user->socket);
}
