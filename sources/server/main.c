/*
** main.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/sources/server
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu>
**
** Started on  Thu Jun 15 14:29:06 2017 Matthias Prost
** Last update	Thu Jun 15 18:35:10 2017 Full Name
*/

#include "server.h"

// t_commands g_commands [COMMANDS] = {
//   {"NICK", &nickCommand},
// };


int	s_error(char *str)
{
  perror(str);
  exit(EXIT_FAILURE);
}

void		serverInit(t_env *env, char *port)
{
  int		i;

  i = -1;
  while (++i != MAX_FD)
    env->users[i].socket = -1;
  memset(env->fd_type, FD_FREE, MAX_FD);
  env->port = atoi(port);
  createServer(env);
}

void  args(t_env env, char **av)
{
  (void)env;
  (void)av;
}

int		printUsage()
{
  printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2"
          "... -c clientsNb -f freq\n\tport\t\t is the port number\n"
          "\twidth\t\t is the width of the world\n"
          "\theight\t\t is the height of the world\n"
          "\tnameX\t\t is the name of the team X\n"
          "\tclientsNb\t is the number of authorized clients per team\n"
          "\tfreq\t\t is the reciprocal of time unit for"
          "execution of actions\n");
  return (-1);
}

int		main(int ac, char **av)
{
  t_env		env;

  (void)ac;
  if (strcmp(av[1], "-help") == 0)
    return (printUsage());
  serverInit(&env, av[1]);
  serverLoop(&env);
  return (0);
}
