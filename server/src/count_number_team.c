/*
** count_number_team.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/server/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 29 18:27:34 2017 Matthias Prost
** Last update Thu Jun 29 18:40:51 2017 Matthias Prost
*/

#include "server.h"

int   count_number_team(char *str, t_env  *env)
{
  int   i;
  int   counter;

  counter = 0;
  while (++i != MAX_FD)
  {
    if (env->users[i].teamName != NULL &&
        strcmp(env->users[i].teamName, str) == 0)
          counter++;
  }
  return (counter);
}
