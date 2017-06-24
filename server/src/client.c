/*
** client.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 17:35:09 2017 Matthias Prost
** Last update Thu Jun 22 16:29:04 2017 Leo Hubert Froideval
*/

#include "server.h"

t_params g_params [NBR_PARAMS] = {
  {"move", &moveParam},
};

void  checkParams(t_env *env, char *msg)
{
  char    **tab;
  int     i;

  i = -1;
  msg = epurStr(msg);
  tab = toWordtab(msg, ' ');
  while (++i != NBR_PARAMS)
  {
    if (strncmp(tab[0], g_params[i].params, strlen(tab[0])) == 0)
    {
      g_params[i].p(env, tab);
      break;
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
      	env->users[i].socket = -1;
        env->users[i].lvl = 0;
        env->users[i].posX = 0;
        env->users[i].posY = 0;
        env->users[i].teamName = NULL;
      	break;
      }
}

void		clientRead(t_env *env, int fd)
{
  char		*buff;
  t_users user;

  buff = xmalloc(2048);
  memset(buff, 0, 2048);
  get_user(env, fd, &user);
  if (recv(fd, buff, 2048, MSG_DONTWAIT) > 0)
  {
    printf("<-- Received: \"%s\" from socket %d\n", epurStr(buff), fd);
    if (user.teamName == NULL)
      checkParams(env, buff);
    free(buff);
  }
  else
  {
    removeUserTab(env, fd);
    printf("Connection closed from socket %d\n", fd);
    free(buff);
    close(fd);
    env->fd_type[fd] = FD_FREE;
  }
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
        printf("Socket: %d\tlvl: %d\t\tposY: %d\t\tposX: %d\t\tdirection: %d\n",
          env->users[i].socket, env->users[i].lvl, env->users[i].posX,
          env->users[i].posY, env->users[i].direction);
      	break;
      }
}

void		addClient(t_env *env, int s)
{
  socklen_t	client_sin_len;
  SOCKADDR_IN	client_sin;
  int		cs;

  client_sin_len = sizeof(client_sin);
  if ((cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len)) == -1)
    s_error("accept");
  addUserTab(env, cs);
  dprintf(cs, "WELCOME\n");
  printf("--> Sent: \"WELCOME\" to socket %d\n", cs);
  env->fd_type[cs] = FD_CLIENT;
  env->fct_read[cs] = clientRead;
  env->fct_write[cs] = NULL;
}
