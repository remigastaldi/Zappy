/*
** server_loop.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 17:18:43 2017 Matthias Prost
** Last update	Wed Jun 21 16:27:22 2017 Full Name
*/

#include "server.h"

void		serverRead(t_env *env, int fd)
{
  printf("New client connected on port %d\n", env->port);
  addClient(env, fd);
}

void		createServer(t_env *env)
{
  SOCKADDR_IN	sin;
  int		s;

  s = socket(PF_INET, SOCK_STREAM, 0);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(env->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    s_error("bind");
  if (listen(s, 42) == -1)
    s_error("listen");
  printf("Server started on port %d\nSize of the world: %d x %d\n"
          "Max clients per Team: %d\nFrequency: %d\n",
          env->port, env->width, env->height, env->clientsNb, env->freq);
  printf("Number of ressources: %d\n", env->nbrRessources);
  display_names(env->names);
  env->fd_type[s] = FD_SERVER;
  env->fct_read[s] = serverRead;
  env->fct_write[s] = NULL;
}

void		serverLoop(t_env *env)
{
  int		fd_max;
  fd_set	fd_read;
  int		i;

  while (1)
    {
      fd_max = 0;
      FD_ZERO(&fd_read);
      i = -1;
      while (++i < MAX_FD)
	if (env->fd_type[i] != FD_FREE)
	  {
	    FD_SET(i, &fd_read);
	    fd_max = i;
	  }
      if (select(fd_max + 1, &fd_read, NULL, NULL, NULL) == -1)
	perror("select");
      i = -1;
      while (++i < MAX_FD)
	if (FD_ISSET(i, &fd_read))
	  env->fct_read[i](env, i);
    }
}
