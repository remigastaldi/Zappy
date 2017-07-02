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

void	display_names(char **tab)
{
  int	i;

  i = -1;
  printf("Names of teams: ");
  while (tab[++i])
    printf("%s, ", tab[i]);
  printf("\n");
}

void	print_map(t_env *env)
{
  int	x;
  int	y;

  x = -1;
  y = -1;
  while (++y != env->height)
    {
      while (++x != env->width)
	{
	  printf("Position: y = %d, x = %d  \t", y, x);
	  printf("line: %d ", env->map[y][x].linemate);
	  printf("derau: %d ", env->map[y][x].deraumere);
	  printf("sibur: %d ", env->map[y][x].sibur);
	  printf("mendi: %d ", env->map[y][x].mendiane);
	  printf("phir: %d ", env->map[y][x].phiras);
	  printf("thys: %d ", env->map[y][x].thystame);
	  printf("food: %d\n", env->map[y][x].food);
	}
      x = -1;
    }
}

void	print_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i])
    printf("%s - ", tab[i]);
  printf("\n");
}

void	print_error(char *str)
{
  printf("%s\n", str);
  exit(EXIT_FAILURE);
}
