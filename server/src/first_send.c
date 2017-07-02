/*
** first_send.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Sun Jul  2 22:32:04 2017 Matthias Prost
** Last update Sun Jul  2 23:23:12 2017 Matthias Prost
*/

#include "server.h"

void		first_send(int counter, int fd, t_env *env)
{
  dprintf(fd, "%d\n", counter);
  dprintf(fd, "%d %d\n", env->width, env->height);
  printf("--> Sent: \"%d\" to socket %d\n", counter, fd);
  printf("--> Sent: \"%d %d\" to socket %d\n", env->width,
    env->height, fd);
}
