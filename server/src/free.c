/*
** free.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Tue Jun 27 16:33:53 2017 gastal_r
** Last update Sun Jul  2 19:20:41 2017 gastal_r
*/

#include    "utilities.h"

void        free_env(t_env *env)
{
  int   i;

  i = -1;
  while (env->map[++i])
    free(env->map[i]);
  free(env->map);
  i = -1;
  while (env->names[++i])
    free(env->names[i]);
  free(env->names);
  i = -1;
  while (env->users[++i].teamName)
  {
    if (env->users[i].teamName != NULL)
      free(env->users[i].teamName);
  }
}

void      free_tab(char **tab)
{
  int   i;

  i = -1;
  if (tab == NULL)
    return;
  while (tab[++i])
    free(tab[i]);
  free(tab);
}
