/*
** client.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 17:35:09 2017 Matthias Prost
** Last update	Thu Jun 15 17:44:34 2017 Full Name
*/

#include "server.h"

void		sendToAll(t_env *env, int fd, char *msg)
{
  int		i;
  t_users	user;

  i = -1;
  while (++i != MAX_FD)
  if (env->users[i].socket == fd)
  {
    user = env->users[i];
    break;
  }
  i = -1;
  while (++i != MAX_FD)
  {
    if (env->users[i].socket != -1 &&
        strcmp(user.chan, env->users[i].chan) == 0)
    {
      dprintf(env->users[i].socket, "%s: %s\n", user.nick, msg);
    }
  }
}

void		removeUserTab(t_env *env, int socket)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    if (env->users[i].socket == socket)
      {
	printf("Remove socket nbr %d on position nbr %d\n", socket, i);
	env->users[i].socket = -1;
	free(env->users[i].nick);
	env->users[i].nick = NULL;
	break;
      }
}

void		clientRead(t_env *env, int fd)
{
  char		*buff;

  if ((buff = get_next_line(fd)) != NULL)
  {
    printf("%d: %s\n", fd, epurStr(buff));
    sendToAll(env, fd, epurStr(buff));
  }
  else
  {
    removeUserTab(env, fd);
    printf("%d: Connection closed\n", fd);
    close(fd);
    env->fd_type[fd] = FD_FREE;
  }
}

void		addClient(t_env *env, int s)
{
  socklen_t	client_sin_len;
  SOCKADDR_IN	client_sin;
  int		cs;

  client_sin_len = sizeof(client_sin);
  if ((cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len)) == -1)
    {
      perror("accept");
      exit(-1);
    }
  dprintf(cs, "Welcome!\r\n");
  env->fd_type[cs] = FD_CLIENT;
  env->fct_read[cs] = clientRead;
  env->fct_write[cs] = NULL;
}
