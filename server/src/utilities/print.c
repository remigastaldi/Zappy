/*
** print.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Jun 21 16:25:15 2017 Matthias Prost
** Last update	Wed Jun 21 16:28:25 2017 Full Name
*/

#include "utilities.h"

void  display_tab(char **tab)
{
  int   i;

  i = -1;
  while (tab[++i])
    printf("%s\n", tab[i]);
}
