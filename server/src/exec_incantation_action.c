/*
** exec_incantation_action.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 29 18:06:12 2017 Matthias Prost
** Last update Fri Jun 30 15:10:02 2017 Matthias Prost
*/

#include "server.h"

int		ressources[8][6] = {
  {0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0},
  {2, 0, 1, 0, 2, 0},
  {1, 1, 2, 0, 1, 0},
  {1, 2, 1, 3, 0, 0},
  {1, 2, 3, 0, 1, 0},
  {2, 2, 2, 2, 2, 1}
};

void  takeOffRessources(t_users *user)
{
  user->inventory.linemate -= ressources[user->lvl][0];
  user->inventory.deraumere -= ressources[user->lvl][1];
  user->inventory.sibur -= ressources[user->lvl][2];
  user->inventory.mendiane -= ressources[user->lvl][3];
  user->inventory.phiras -= ressources[user->lvl][4];
  user->inventory.thystame -= ressources[user->lvl][5];
}

int  counterUsersInc(t_env *env, t_users *user)
{
  int   i;
  int   counter;

  i = -1;
  counter = 0;
  while (++i != MAX_FD)
  {
    if (env->users[i].socket != -1 && env->users[i].posX == user->posX
        && env->users[i].posY == user->posY && env->users[i].lvl == user->lvl)
          counter++;
  }
  return (counter);
}

int   checkLevel(t_env *env, t_users *user)
{
  int   userAvailable;

  userAvailable = counterUsersInc(env, user);
  if (user->lvl == 1 && userAvailable > 0)
    return (1);
  else if (user->lvl == 2 && userAvailable >= 1)
    return (1);
  else if (user->lvl == 3 && userAvailable > 1)
    return (1);
  else if (user->lvl == 4 && userAvailable > 3)
    return (1);
  else if (user->lvl == 5 && userAvailable > 3)
    return (1);
  else if (user->lvl == 6 && userAvailable > 5)
    return (1);
  else if (user->lvl == 7 && userAvailable > 5)
    return (1);
  return (0);
}

void  incantationAction(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  if (user->socket != -1)
  {
    if (checkLevel(env, user) == 1)
    {
      user->lvl += 1;
      dprintf(user->socket, "Current level: %d\n", user->lvl);
      printf("User with socket %d level up to %d\n", user->socket, user->lvl);
      printf("--> Sent \"Current level: %d\" to socket %d\n",
              user->lvl, user->socket);
      user->lock = false;
    }
    else
    {
      dprintf(user->socket, "ko\n");
      printf("--> Sent \"ko\" to socket %d\n", user->socket);
    }
  }
}

void  forkAction(t_env *env, char **msg, t_users *user)
{
  (void)msg;
  t_action *action;
  char     **new;

  if (user->socket != -1)
  {
    printf("--> Sent \"ok\" to socket %d\n", user->socket);
    dprintf(user->socket, "ok\n");
    new = toWordtab("Egg", ' ');
    env->map[user->posY][user->posX].egg += 1;
    action = newAction(env->queue, user, &eggAction,
                        600000000 / env->freq);
    addActionData(action, env, new);
  }
}
