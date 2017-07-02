/*
** client.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 17:35:09 2017 Matthias Prost
** Last update Sun Jul  2 22:00:06 2017 Matthias Prost
*/

#include "server.h"

t_params g_params [NBR_PARAMS] = {
  {"Forward", &forwardParam},
  {"Right", &rightParam},
  {"Left", &leftParam},
  {"Look", &lookParam},
  {"Connect_nbr", &connect_nbrAction},
  {"Inventory", &inventoryParam},
  {"Take", &takeParam},
  {"Set", &setParam},
  {"Incantation", &incantationParam},
  {"Fork", &forkParam},
  {"Broadcast", &broadcastParam},
  {"ko", &koParam}
};

void		checkParams(t_env *env, char *msg, int fd)
{
  char		**tab;
  int		i;
  t_users	*user;
  int		check;

  i = -1;
  check = 0;
  msg = epurStr(msg);
  tab = toWordtab(msg, ' ');
  user = get_user(env, fd);
  while (++i != NBR_PARAMS)
    {
      if (strcmp(tab[0], g_params[i].params) == 0 && fd != -1)
	{
	  (*g_params[i].p)(env, tab, user);
	  check = 1;
	  break;
	}
    }
  if (check != 1)
    (*g_params[NBR_PARAMS - 1].p)(env, tab, user);
}

int		checkNames(t_env *env, char *buff)
{
  int		i;

  i = -1;
  while (env->names[++i])
    if (strcmp(env->names[i], epurStr(buff)) == 0)
      return (0);
  return (-1);
}

void		joinTeam(t_env *env, char *buff, int fd)
{
  struct	timeval curr_time;
  t_users	*user;
  int		counter;

  counter = 0;
  user = get_user(env, fd);
  gettimeofday(&curr_time, NULL);
  if (checkNames(env, buff) == 0 &&
      (counter = env->clientsNb - countNumberTeam(epurStr(buff), env)))
    {
      if (counter >= 1 && fd != -1)
	{
	  user->food_timer = curr_time.tv_sec * 1000000 + curr_time.tv_usec +
	    (126000000 / env->freq);
	  user->teamName = strdup(epurStr(buff));
	}
      if (user != NULL && counter < 1 && fd != -1)
	{
	  removeUserTab(env, user->socket);
	  env->fd_type[fd] = FD_FREE;
	}
    }
  if (user != NULL && user->socket != -1)
      first_send(counter, fd, env);
}

void		clientRead(t_env *env, int fd)
{
  char		buff[2048];
  t_users	*user;

  memset(buff, 0, 2048);
  user = get_user(env, fd);
  if (recv(fd, buff, 2048, MSG_DONTWAIT) > 0)
    {
      printf("<-- Received: \"%s\" from socket %d\n", epurStr(buff), fd);
      if (user != NULL && fd != -1 && user->teamName != NULL)
	checkParams(env, buff, fd);
      else
	joinTeam(env, epurStr(buff), fd);
    }
  else
    {
      removeUserTab(env, fd);
      env->fd_type[fd] = FD_FREE;
      printf("Connection closed from socket %d\n", fd);
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
