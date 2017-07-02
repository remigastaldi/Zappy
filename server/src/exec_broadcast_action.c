/*
** exec_broadcast_action.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Fri Jun 30 16:23:06 2017 Matthias Prost
** Last update Sun Jul  2 15:26:07 2017 gastal_r
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

void      bubble_sort(t_distance *user_distance, t_users *user, t_env *env, char **msg)
{
  int        i;
  double     buffer;
  int        broad;
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
  if (user_dest != NULL && user->socket != -1 && strcmp(msg[0], "Fork") != 0)
    {
      delete_all_fd_actions(env, user_dest->user->socket);
      broad = broadcast(user, user_dest->user, env);
      dprintf(user_dest->user->socket, "message %d\n",
              broad);
      printf("--> Sent: \"message %d\" to socket %d\n", broad,
              user_dest->user->socket);
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
    if (env->users[i].lock == false && env->users[i].socket != -1
      && env->users[i].socket != user->socket && env->users[i].teamName != NULL
      && user->teamName && strcmp(env->users[i].teamName, user->teamName) == 0
      && env->users[i].lvl == user->lvl)
          {
            printf("Distance between socket %d and socket %d: %lf\n",
              user->socket, env->users[i].socket,
                distance_users(user, &env->users[i]));
            user_distance[a].user = xmalloc(sizeof(t_users));
            memcpy(user_distance[a].user, &env->users[i], sizeof(t_users));
            // user_distance[a].user = memcpyenv->users[i];
            user_distance[a].distance = distance_users(user, &env->users[i]);
            a++;
          }
  }
  bubble_sort(&user_distance[0], user, env, msg);
  if (user->socket != -1)
  {
    dprintf(user->socket, "ok\n");
    printf("--> Sent: \"ok\" to socket %d\n", user->socket);
  }
}
