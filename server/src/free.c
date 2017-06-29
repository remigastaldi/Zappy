/*
** free.c for Zappy in /home/gastal_r/rendu/Zappy/server/src/
**
** Made by gastal_r
** Login   <remi.gastaldi@epitech.eu>
**
** Started on  Tue Jun 27 16:33:53 2017 gastal_r
** Last update Thu Jun 29 18:41:49 2017 gastal_r
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
}

void      free_tab(char **tab)
{
  int   i;

  i = -1;
  while (tab[++i])
    free(tab[i]);
  free(tab);
}
