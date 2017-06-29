/*
** client_management.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Mon Jun 26 15:25:06 2017 Matthias Prost
** Last update Wed Jun 28 18:56:39 2017 Leo Hubert Froideval
*/

#include "server.h"

void    initInventory(t_env *env, int i)
{
  env->users[i].inventory.food = 10;
  env->users[i].inventory.linemate = 0;
  env->users[i].inventory.deraumere = 0;
  env->users[i].inventory.sibur = 0;
  env->users[i].inventory.mendiane = 0;
  env->users[i].inventory.phiras = 0;
  env->users[i].inventory.thystame = 0;
}

void		addUserTab(t_env *env, int socket)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    if (env->users[i].socket == -1)
      {
      	env->users[i].socket = socket;
        env->users[i].lvl = 1;
        env->users[i].posX = rand() % env->width;
        env->users[i].posY = rand() % env->height;
        env->users[i].direction = rand() % 4;
        env->users[i].teamName = NULL;
        initInventory(env, i);
        printf("Socket: %d\tlvl: %d\t\tposY: %d\t\tposX: %d\t\tdirection: %d\n",
          env->users[i].socket, env->users[i].lvl, env->users[i].posY,
          env->users[i].posX, env->users[i].direction);
      	break;
      }
}

void		removeUserTab(t_env *env, int socket)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
  if (env->users[i].socket == socket)
  {
    env->users[i].socket = -1;
    env->users[i].lvl = 0;
    env->users[i].posX = 0;
    env->users[i].posY = 0;
    env->users[i].teamName = NULL;
    break;
  }
}
