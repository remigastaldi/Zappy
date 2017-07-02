/*
** exec_client.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Jun 28 16:38:50 2017 Matthias Prost
** Last update Sun Jul  2 22:02:15 2017 Matthias Prost
*/

#include "server.h"

void		connect_nbrAction(t_env *env, char **msg, t_users *user)
{
  int		i;
  int		counter;

  i = -1;
  counter = 0;
  (void)msg;
  if (user->socket != -1)
    {
      while (env->names[++i])
	{
	  printf("user teamname: %s - env teamname: %s\n",
		 user->teamName, env->names[i]);
	  if (strcmp(user->teamName, env->names[i]) == 0)
	    counter++;
	}
      counter = env->clientsNb - counter;
      dprintf(user->socket, "%d\n", counter);
      printf("--> Sent: \"%d\" to socket %d\n", counter, user->socket);
    }
}
