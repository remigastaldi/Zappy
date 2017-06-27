/*
** server_loop.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 17:18:43 2017 Matthias Prost
** Last update Tue Jun 27 17:46:17 2017 sellet_f
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
  display_names(env->names);
  print_map(env);
  printf("Number of ressources: %d\n", env->nbrRessources);
  env->fd_type[s] = FD_SERVER;
  env->fct_read[s] = serverRead;
  env->fct_write[s] = NULL;
}


void		serverLoop(t_env *env)
{
  int		fd_max;
  fd_set	fd_read;
  int		i;
  struct timeval old;
  long old_t;
  struct timeval current;
  long current_t;
  t_gui			*GUI;

  struct timeval timeout;

  gettimeofday(&old, NULL);
  gettimeofday(&current, NULL);

  old_t = ((unsigned long long)old.tv_sec * 1000000) + old.tv_usec;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  if ((GUI = malloc(sizeof(t_gui))) == NULL)
    return;
  initGUI(GUI, env);
  while (sfRenderWindow_isOpen(GUI->_win))
    {
      gettimeofday(&current, NULL);
      current_t = ((unsigned long long)current.tv_sec * 1000000) + current.tv_usec;

      if (current_t > (old_t + 1000000) / 2) // (old_t + 1000000) = 1 seconde
      {
        gettimeofday(&old, NULL);
        old_t = ((unsigned long long)old.tv_sec * 1000000) + old.tv_usec;
      }
        //Check workingQueue
      drawGUI(GUI, env);
      fd_max = 0;
      FD_ZERO(&fd_read);
      i = -1;
      while (++i < MAX_FD)
	if (env->fd_type[i] != FD_FREE)
	  {
	    FD_SET(i, &fd_read);
	    fd_max = i;
	  }
      if (select(fd_max + 1, &fd_read, NULL, NULL, &timeout) == -1)
	perror("select");
      i = -1;
      while (++i < MAX_FD)
	if (FD_ISSET(i, &fd_read))
	  env->fct_read[i](env, i);
    }
  destroyGUI(GUI);
}
